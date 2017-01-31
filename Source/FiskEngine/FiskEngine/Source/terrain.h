#pragma once

#include <SFML/Graphics.hpp>

// Todo: Remove
enum TerrainType
{
	TerrainType_Grass,
	TerrainType_Water,
	TerrainType_Mountain
};


class Terrain
{
	//Todo - move shape stuff out of here
public:
	Terrain(float size, sf::Color color, TerrainType type, float movementCost, bool isTraversable) {
		m_terrainShape = sf::CircleShape(size, 6);
		m_terrainShape.setFillColor(color);
		m_terrainShape.setOutlineColor(sf::Color::Blue);
		m_terrainShape.setOutlineThickness(1.0);
		m_type = type;
		m_isTraversable = isTraversable;
		m_movementCost = movementCost;			 
	};
	~Terrain();

	bool isTraversable() { return m_isTraversable; };
	float getMovementCost() { return m_movementCost; };
	TerrainType getTerrainType() { return m_type; };
	sf::CircleShape getShape() { return m_terrainShape; };

private:
	sf::CircleShape m_terrainShape;
	sf::Color m_color;

	bool m_isTraversable;
	float m_movementCost;
	TerrainType m_type;
};

