#pragma once

#include <unordered_set>
#include <SFML/Graphics.hpp>
#include "Hex.h"


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
	std::unordered_set<Hex> *getHexes() { return &m_hex; }
	sf::CircleShape *getDebugHexagon() { return &m_debugHexagon; }
	float getHexSize() { return m_hexSize; }

	//TODO - make static and fix 
	float *getPixelPositionOfHex(const Hex hex) {
			float *pos = new float[2];
			pos[0] = m_hexSize * sqrt(3.0) * (hex.x + hex.y / 2.0);
			pos[1] = m_hexSize * 3.0 / 2.0 * hex.y;
			return pos;
	};
private:

	mutable std::unordered_set<Hex> m_hex;
	int m_rows;
	int m_cols;
	float m_hexSize;
	MapShape m_shape;

	// TODO: Decide on how to render stuff
	// Used for debug display of map
	sf::CircleShape m_debugHexagon;
};

