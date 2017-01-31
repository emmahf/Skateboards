#pragma once

#include <unordered_set>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include "terrain.h"
#include <queue>

enum MapShape
{
	MapShape_Rectangular,
	MapShape_Parallell
};

// Basic structure of Hexmap
// Note: This would be best to keep small so that it can be easily used for various purposes (AI, render etc)
// Note-alternatice: Make this into the navgrid instead and use a different representation for the actual graphics. 

struct HexData {
	Terrain *terrain;
	int distance;
	Hex * m_cameFrom;
	Hex * m_self;
	bool m_visited;
	double m_costSoFar;

	HexData(Terrain *t, Hex *h) : terrain(t), distance(0), m_visited(false), m_costSoFar(0.0), m_self(h){};
};

struct HexPriority {
	Hex * m_self;
	double m_priority;

	HexPriority(Hex *h, double p) : m_self(h), m_priority(p) {};
};


struct LessThanByPriority
{
	bool operator()(const HexPriority& lhs, const HexPriority& rhs) const
	{
		return lhs.m_priority < rhs.m_priority;
	}
};


struct LessThanByCost
{
	bool operator()(const HexData& lhs, const HexData& rhs) const
	{
		return lhs.m_costSoFar < rhs.m_costSoFar;
	}
};

class NavGrid
{

public:

	NavGrid(int rows, int cols, float size, MapShape shape);
	~NavGrid();

	void clearDistanceField();

	int dq, dr;

	std::string getDebugString();
	std::unordered_map<Hex, HexData*> *getHexes() { return &m_hex; }
	HexData* getHexData(Hex h) { return m_hex[h]; };

	sf::CircleShape *getDebugHexagon() { return &m_debugHexagon; }
	float getHexSize() { return m_hexRadius; }
	bool isHexOnMap(Hex h) { return m_hex.find(h) != m_hex.end(); }

	void updateHexTerrain(Hex hex);


	void computeDistanceField(Hex destination);
	void computeDistanceField();
	void setGoal(sf::Vector2i localPosition);
	void setGoal(int hx, int hy);

	void NavGrid::debugMouseInput(sf::Vector2i localPosition);

	//Todo: Move out rendering
	//Todo: Decouple from PathFinder (or just do the pathFinder stuff in here)
	//void drawMap(sf::RenderWindow * rw, PathFinder * navGrid, sf::Font * debugFont);
	void drawMap(sf::RenderWindow * rw, sf::Font * debugFont);

	//Todo: Use point helperclass?
	float *getPixelPositionOfHex(const Hex hex) {
			//Todo: This makes assumptions on x,y coordinate system and position of origin
			float *pos = new float[2];
			pos[0] = m_hexRadius * sqrt(3.0f) * (hex.x + hex.y / 2.0f);
			pos[1] = m_hexRadius * 3.0f / 2.0f * hex.y;
			return pos;
	};

	//Todo: This is not correct
	float *getCenterPixelPositionOfHex(const Hex hex) {
		float *pos = new float[2];
		pos[0] = m_hexRadius * sqrt(3.0f) * (hex.x + hex.y / 2.0f) + m_hexRadius;
		pos[1] = m_hexRadius * 3.0f / 2.0f * hex.y + m_hexRadius;
		return pos;
	};

	#pragma optimize( "", off )

	// TODO: Make it work with window scaling
	// Either by getting scale as argument, or by scaling values before sending them in
	Hex getHexFromPixelPosition(int px, int py) {
		/*
		// Should work together within cubic round. Neiter does. 
		float q = (px * sqrt(3.0f) / 3.0f - (py) / 3.0f) / m_hexSize;
		float r = ( py) * 2.0f / 3.0f / m_hexSize;
		float s = -q - r;
		*/
		
		// Fuckin magic courtesy of someone called Charles Dambers. Branchless pixel -> hex ftw. 
		float x = (px - m_hexRadius) / (m_hexRadius * sqrt(3.0f));
		float y = (py - m_hexRadius) / (m_hexRadius * sqrt(3.0f));

		float temp = floor(x + sqrt(3.0f) * y + 1.0f);
		float r = floor((temp + floor(-x + sqrt(3.0f) * y + 1.0f)) / 3.0f);
		float q = floor((floor(2.0f * x + 1.0f) + temp) / 3.0f) - r;

		float s = -q - r;
		
		/*
		//For debug, requires windows.h include. 
		std::string test = "Unrounded Q:" + std::to_string(q) + "  R:" + std::to_string(r) + "  S:" + std::to_string(s) + "\n";
		OutputDebugStringA(test.c_str());
//		Hex::cubicRound(q, r , s);
		test = "Rounded: Q:" + std::to_string(q) + "  R:" + std::to_string(r) + "  S:" + std::to_string(s) + "\n";
		OutputDebugStringA(test.c_str());
		*/

		return Hex( (int) q, (int)r);
	};
	#pragma optimize( "", on )



private:

	//Todo: Unordered map should only be used for the storing of data, example terrain. 
	//For fast traversal the map should be store in an array.
	//Then we can both quickly travser (go through array), and quickly get data (from hash) in constant time
	//If for( hex: hexes){ terrain = m_Hex[hex]}
	mutable std::unordered_map<Hex, HexData*> m_hex;
	int m_rows;
	int m_cols;
	float m_hexRadius;
	MapShape m_shape;

	// TODO: Decide on how to render stuff
	// Used for debug display of map
	sf::CircleShape m_debugHexagon;
	
	std::unordered_map<int, Terrain*> terrains;
	
	//Terrains
	Terrain* m_grassTerrain;
	Terrain* m_waterTerrain;
	Terrain* m_mountainTerrain;

	// Distance field to goal
	Hex * m_goal;
	std::priority_queue<HexPriority, std::vector<HexPriority>, LessThanByPriority> m_frontier;
	std::vector<Hex> m_test;

};

