#include "Enemies.h"
#include "assert.h"

//TODO: SWITCH TO REAL MATH-LIBRARY!
float mag(sf::Vector2f v)
{
	return std::sqrt(std::pow(v.x, 2) + std::pow(v.y, 2));
}

sf::Vector2f norm(sf::Vector2f v)
{
	return v / mag(v);
}


#pragma optimize( "", off )
Enemies::Enemies(NavGrid* nav, unsigned int spawnRate) :
	m_navGrid(*nav),
	m_spawnRate(spawnRate),
	m_distY(0,600), //todo: remove magic numbers
	m_distX(0,800)	//todo: remove magic numbers
{
	m_aliveEnemies = 100;

	initEnemiesSingleBurst(m_aliveEnemies);
		
	//Debug shape
	m_enemyShape = sf::CircleShape(5);
	m_enemyShape.setFillColor(sf::Color::Blue);
	m_enemyShape.setOutlineColor(sf::Color::Blue);
	m_enemyShape.setOutlineThickness(2.0);
}

void Enemies::initEnemiesSingleBurst(int numberOfEnemies) 
{	
	assert(numberOfEnemies <= 100);

	//Initalize enemies (here - single burst)
	for (size_t i = 0; i < numberOfEnemies; i++)
	{
		Hex *h;
		sf::Vector2f pos;
		do
		{
			std::mt19937 randX(m_seed());
			std::mt19937 randY(m_seed());
			pos = sf::Vector2f((float)m_distX(randX), (float)m_distY(randY));
			h = &m_navGrid.getHexFromPixelPosition(pos.x, pos.y);
		} while (!m_navGrid.isHexOnMap(*h)); //Todo: Must also check that terrain is valid



		sf::Vector2f vel(0, 0);


		Hex* target = m_navGrid.getHexData(*h)->m_cameFrom;
		if (target != nullptr)
		{
			float *posT = m_navGrid.getCenterPixelPositionOfHex(*target);
			vel = sf::Vector2f(posT[0] - pos.x, posT[1] - pos.y);
			vel = norm(vel);
		}
		m_enemies[i] = EnemyData(vel, pos, 0.05, &m_navGrid.getHexFromPixelPosition(pos.x, pos.y));
	}
}

Enemies::~Enemies()
{
}


void Enemies::update()
{
	for (size_t i = 0; i < m_aliveEnemies; i++) 
	{	
		//Update positions
		m_enemies[i].position += m_enemies[i].velocity*m_enemies[i].speed; // * deltaTime; //(Todo: should depend on simtime - need to decide how to do sim in engine
		
		//Check if need to update target
		Hex currentHex = m_navGrid.getHexFromPixelPosition(m_enemies[i].position.x, m_enemies[i].position.y);

		if(m_navGrid.isHexOnMap(currentHex)) // && m_enemies[i].currentHex != &currentHex)
		{
			Hex* target = m_navGrid.getHexData(currentHex)->m_cameFrom;

			if (target != nullptr) 
			{
				float *posT = m_navGrid.getCenterPixelPositionOfHex(*target);
				m_enemies[i].velocity = sf::Vector2f(posT[0] - m_enemies[i].position.x, posT[1] - m_enemies[i].position.y);
				m_enemies[i].velocity = norm(m_enemies[i].velocity);
				m_enemies[i].currentHex = &currentHex;
			}
		}

	}
}

#pragma optimize( "", on )
void Enemies::draw(sf::RenderWindow *rw)
{
	for (size_t i = 0; i < m_aliveEnemies; i++)
	{
		m_enemyShape.setPosition(m_enemies[i].position);
		rw->draw(m_enemyShape);
	}
}