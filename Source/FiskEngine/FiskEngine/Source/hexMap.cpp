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

	//Todo: Decide which structure to use
	m_grassTerrain = new Terrain(size, sf::Color(140,250,100), TerrainType_Grass, 0.0, true);
	m_waterTerrain = new Terrain(size, sf::Color(50, 50, 200), TerrainType_Water, 1.0, true);
	m_mountainTerrain = new Terrain(size, sf::Color(140, 140, 140), TerrainType_Mountain, 0.0, false);

	switch (m_shape) {

	case MapShape_Rectangular:

		for (int r = 0; r < rows; r++)
		{
			int r_offset = r >> 1; //  = floor(r/2)
			for (int q = -r_offset; q < cols - r_offset; q++) {
				m_hex.insert({ Hex(q, r, -q - r), m_grassTerrain });
			}
		}
		break;

	case MapShape_Parallell:
		for (int q = 0; q <= rows; q++) {
			for (int r = 0; r <= cols; r++) {
				m_hex.insert({ Hex(q, r, -q - r), m_grassTerrain });
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

//Used for debug editing
void HexMap::debugMouseInput(sf::Vector2i localPosition) {
	Hex hex = getHexFromPixelPosition(localPosition.x, localPosition.y);
	updateHexTerrain(hex);
}

//Used for debug editing
void HexMap::updateHexTerrain(Hex hex) {
	
	Terrain *terrain = m_hex[hex];
	switch (terrain->getTerrainType()) {
		case TerrainType_Grass:
			m_hex[hex] = m_waterTerrain;
			break;
		case TerrainType_Water:
			m_hex[hex] = m_mountainTerrain;
			break;
		case TerrainType_Mountain:
			m_hex[hex] = m_grassTerrain;
			break;
		default:
			break;
	}
}

void HexMap::drawMap(sf::RenderWindow *rw, sf::Font *debugFont) {

	// REMOVE!
	{
		sf::Text hexText;
		hexText.setFont(*debugFont);
		hexText.setCharacterSize(10);
		hexText.setFillColor(sf::Color::Black);
		hexText.setStyle(sf::Text::Regular);

		for (const std::pair<Hex, Terrain*> tile : m_hex)
		{
			Hex hex = tile.first;
			sf::CircleShape terrain = tile.second->getShape();
			hexText.setString(hex.toString());
			float *pos = getPixelPositionOfHex(hex);

			//OutputDebugStringA(( hex.toString() + std::to_string(pos[0]) + "," + std::to_string(pos[1]) + "\n").c_str());

			terrain.setPosition(pos[0], pos[1] + 50);
			rw->draw(terrain);

			hexText.setPosition(pos[0] + m_hexSize / 2.0, pos[1] + 50 + m_hexSize / 2.0);
			rw->draw(hexText);
		}
	}

}

std::string HexMap::getDebugString()
{	
	std::string map;
	for (const std::pair<Hex, Terrain*> tile : m_hex) 
	{
		map += (tile.first.toString() +  "\n");
	}
	return map;
}
