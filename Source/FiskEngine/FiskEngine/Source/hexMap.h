#pragma once

#include <unordered_set>
#include "Hex.h"


enum MapShape
{
	MapShape_Rectangular,
	MapShape_Parallell
};

class HexMap
{

public:

	HexMap(int rows, int cols, float size, MapShape shape);
	~HexMap();


	std::string getDebugString();
	std::unordered_set<Hex> *getHexes() { return &m_hex; }

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
};

