#include "hexMap.h"
#include <string>

HexMap::HexMap(int rows, int cols, float size, MapShape shape) :
	m_rows(rows),
	m_cols(cols),
	m_hexSize(size)
{
	this->m_shape = shape;

	m_debugHexagon = sf::CircleShape(size, 6);
	m_debugHexagon.setFillColor(sf::Color(140, 250, 100));
	m_debugHexagon.setOutlineColor(sf::Color::Blue);
	m_debugHexagon.setOutlineThickness(2.0);

	switch (m_shape) {

	case MapShape_Rectangular:

		for (int r = 0; r < rows; r++)
		{
			int r_offset = r >> 1; //  = floor(r/2)
			for (int q = -r_offset; q < cols - r_offset; q++) {
				m_hex.insert(Hex(q, r, -q - r));
			}
		}
		break;

	case MapShape_Parallell:
		for (int q = 0; q <= rows; q++) {
			for (int r = 0; r <= cols; r++) {
				m_hex.insert(Hex(q, r, -q - r));
			}
		}
		break;

	default:
		break;

	}

}

HexMap::~HexMap()
{
}

std::string HexMap::getDebugString()
{	
	std::string map;
	for (const Hex hex : m_hex) 
	{
		map += (hex.toString() +  "\n");
	}
	return map;
}
