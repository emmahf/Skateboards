#pragma once

#include <unordered_set>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include "Hex.h"
#include "terrain.h"

enum MapShape
{
	MapShape_Rectangular,
	MapShape_Parallell
};

// Basic structure of Hexmap
// Note: This would be best to keep small so that it can be easily used for various purposes (AI, render etc)
class HexMap
{

public:

	HexMap(int rows, int cols, float size, MapShape shape);
	~HexMap();


	std::string getDebugString();
	std::unordered_map<Hex, Terrain*> *getHexes() { return &m_hex; }
	sf::CircleShape *getDebugHexagon() { return &m_debugHexagon; }
	float getHexSize() { return m_hexSize; }
	bool isHexOnMap(Hex h) { return m_hex.find(h) != m_hex.end(); }

	void updateHexTerrain(Hex hex);

	void HexMap::debugMouseInput(sf::Vector2i localPosition);

	//Todo: Move out rendering
	void drawMap(sf::RenderWindow *rw, sf::Font *debugFont);

	//Todo: Use point helperclass?
	float *getPixelPositionOfHex(const Hex hex) {
			//Todo: This makes assumptions on x,y coordinate system and position of origin
			float *pos = new float[2];
			pos[0] = m_hexSize * sqrt(3.0) * (hex.x + hex.y / 2.0);
			pos[1] = m_hexSize * 3.0 / 2.0 * hex.y;
			return pos;
	};

	Hex getHexFromPixelPosition(int px, int py) {
		float q = (px * sqrt(3) / 3 - (py -50.0) / 3) / m_hexSize;
		float r = ( py - 50.0) * 2 / 3 / m_hexSize;
		return Hex( (int) q, (int)r); //TODO: MUST CHANGE TO PROPER ROUND!
	};
private:

	//Todo: Unordered map should only be used for the storing of data, example terrain. 
	//For fast traversal the map should be store in an array.
	//Then we can both quickly travser (go through array), and quickly get data (from hash) in constant time
	//If for( hex: hexes){ terrain = m_Hex[hex]}
	mutable std::unordered_map<Hex, Terrain*> m_hex;
	int m_rows;
	int m_cols;
	float m_hexSize;
	MapShape m_shape;

	// TODO: Decide on how to render stuff
	// Used for debug display of map
	sf::CircleShape m_debugHexagon;
	
	std::unordered_map<int, Terrain*> terrains;
	
	//Terrains
	Terrain* m_grassTerrain;
	Terrain* m_waterTerrain;
	Terrain* m_mountainTerrain;

};

