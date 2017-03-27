#pragma once

#include "NavGrid.h"
#include <SFML/Graphics.hpp>
#include <random>

struct EnemyData //Inherit from general data structure class? Should be lightweight for packing purpose
{
	//Todo: Switch from to sf::Vector2f to some decent standard library
	sf::Vector2f velocity;
	sf::Vector2f position;
	float speed;
	Hex *currentHex;

	EnemyData() { ; };
	EnemyData(sf::Vector2f vel, sf::Vector2f pos, float s, Hex *h) : velocity(vel), position(pos), speed(s), currentHex(h) { ; };
};

class Enemies // Todo: Inherit (?) from a base entity class that have common functions for update, draw, etc
{
public:
	Enemies(NavGrid* nav, unsigned int spawnRate);
	~Enemies();

	void initEnemiesSingleBurst(int numberOfEnemies);

	void update();
	void draw(sf::RenderWindow *rw);

private:
	NavGrid*		m_navGrid;
	EnemyData		m_enemies[100]; //Todo: Dynamic, do we care?
	unsigned int	m_aliveEnemies;
	unsigned int	m_spawnRate;

	//Random distributions
	std::random_device m_seed;
	std::uniform_int_distribution<int> m_distX;
	std::uniform_int_distribution<int> m_distY;

	//Debug Draw
	sf::CircleShape m_enemyShape;
};

