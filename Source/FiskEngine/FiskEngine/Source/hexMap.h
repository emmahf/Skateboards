#pragma once

#include <unordered_set>
#include "Hex.h"

class HexMap
{

public:

	HexMap(int rows, int cols, float size) :
		m_rows(rows),
		m_cols(cols),
		m_hexSize(size)
	{	
		/*
		// Parall..: Rectangular map
		for (int q = 0; q <= rows; q++) {
			for (int r = 0; r <= cols; r++) {
				m_hex.insert(Hex(q, r, -q - r));
			}
		}
		*/
		
		for (int r = 0; r < rows ; r++) 
		{
			int r_offset = r >> 1; //  = floor(r/2)
			for (int q = -r_offset; q < cols - r_offset; q++) {
				m_hex.insert(Hex(q, r, -q - r));
			}
		}
		
	}
	~HexMap();


	std::string getDebugString();
	std::unordered_set<Hex> *getHexes() { return &m_hex; }

	//TODO - make static and fix 
	float *getPixelPositionOfHex(const Hex hex) {
			float *pos = new float[2];
			pos[0] = m_hexSize * sqrt(3) * (hex.x + hex.y / 2);
			pos[1] = m_hexSize * 3 / 2 * hex.x;
			return pos;
	};
private:

	mutable std::unordered_set<Hex> m_hex;
	int m_rows;
	int m_cols;
	float m_hexSize;
};

