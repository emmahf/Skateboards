#include "NavGrid.h"
#include <string>

NavGrid::NavGrid(int rows, int cols, float size, MapShape shape) :
	m_rows(rows),
	m_cols(cols),
	m_hexRadius(size)
{
	this->m_shape = shape;

	dq = dr = 0;
	m_debugHexagon = sf::CircleShape(size, 6);
	m_debugHexagon.setFillColor(sf::Color(140, 250, 100));
	m_debugHexagon.setOutlineColor(sf::Color::Blue);
	m_debugHexagon.setOutlineThickness(2.0);

	//Todo: Decide which structure to use
	m_grassTerrain = new Terrain(size, sf::Color(140,250,100), TerrainType_Grass, 1.0, true);
	m_waterTerrain = new Terrain(size, sf::Color(50, 50, 200), TerrainType_Water, 1.0, false);
	m_mountainTerrain = new Terrain(size, sf::Color(140, 140, 140), TerrainType_Mountain, 5.0, true);


	switch (m_shape) {

	case MapShape_Rectangular:

		for (int r = 0; r < rows; r++)
		{
			int r_offset = r >> 1; //  = floor(r/2)
			for (int q = -r_offset; q < cols - r_offset; q++) {
				Hex h = Hex(q, r, -q - r);
				HexData *data = new HexData(m_grassTerrain, &h);
				m_hex.insert({ h, data });
			}
		}
		break;

	case MapShape_Parallell:
		for (int q = 0; q <= rows; q++) {
			for (int r = 0; r <= cols; r++) {
				Hex h = Hex(q, r, -q - r);
				HexData *data = new HexData(m_grassTerrain, &h);
				m_hex.insert({ h, data });
			}
		}
		break;

	default:
		break;

	}

}

NavGrid::~NavGrid()
{
}

void NavGrid::clearDistanceField() {

	for (const std::pair<Hex, HexData*> tile : m_hex)
	{
		tile.second->m_cameFrom = nullptr;
		tile.second->m_visited = false;
		tile.second->m_costSoFar = 0.0;
	}
}


#pragma optimize( "", off )
void NavGrid::computeDistanceField(Hex destination) {

	if (!this->isHexOnMap(destination))
		return;

	this->clearDistanceField();

	m_hex[destination]->m_cameFrom = new Hex(destination.x, destination.y);
	m_hex[destination]->m_visited = true;
	m_hex[destination]->m_costSoFar = -1.0;

	m_frontier.push(HexPriority(&destination, 0.0));

	while (!m_frontier.empty())
	{
		HexPriority currentHexPriority = m_frontier.top();
		Hex currentHex = *currentHexPriority.m_self;
		std::vector<Hex> neighbours = currentHex.getNeighbours(currentHex);

		if (currentHex.x == 4 && currentHex.y == 3) 
		{
			bool test = false;
		}

		m_frontier.pop();
		for (auto neighbour : neighbours)
		{	

			if (neighbour.x == 4 && neighbour.y == 3)
			{
				bool test = false;
			}

			bool isHexOnMap = this->isHexOnMap(neighbour);
			
			if (!isHexOnMap)
				continue;

			double newCost = currentHexPriority.m_priority + m_hex[neighbour]->terrain->getMovementCost();

			if (m_hex[neighbour]->terrain->isTraversable() &&
				(m_hex[neighbour]->m_costSoFar == 0 || newCost < m_hex[neighbour]->m_costSoFar))
			{
					m_hex[neighbour]->m_cameFrom = new Hex(currentHex.x, currentHex.y);
					m_hex[neighbour]->m_costSoFar = newCost;

					HexPriority prio = HexPriority(new Hex(neighbour), newCost);
					m_frontier.push(prio);
			}
		}

	}

}

#pragma optimize( "", on )

// Create flow map
// Todo: Weigh by terrain
/*
void HexMap::computeDistanceField(Hex destination) {

	if (!this->isHexOnMap(destination))
		return;

	this->clearDistanceField();

	m_hex[destination]->m_cameFrom = new Hex(destination.x, destination.y);
	m_hex[destination]->m_visited = true;
	m_hex[destination]->m_costSoFar = 0.0;
	m_frontier.push(destination);

	while (!m_frontier.empty())
	{
		Hex currentHex = m_frontier.front();
		std::vector<Hex> neighbours = currentHex.getNeighbours(currentHex);

		for (auto neighbour : neighbours)
		{
			if (!this->isHexOnMap(neighbour))
				continue;

			double newCost = m_hex[currentHex]->m_costSoFar + m_hex[neighbour]->terrain->getMovementCost();

			if (m_hex[neighbour]->m_visited == false)
			{
				m_hex[neighbour]->m_visited = true;
				if (m_hex[neighbour]->terrain->isTraversable())
				{
					m_hex[neighbour]->m_cameFrom = new Hex(currentHex.x, currentHex.y);
					m_hex[neighbour]->m_costSoFar = newCost;
					m_frontier.push(neighbour);
				}
			}
		}

		m_frontier.pop();
	}
}
*/
void NavGrid::computeDistanceField()
{
	computeDistanceField(*m_goal);
}

void NavGrid::setGoal(sf::Vector2i localPosition)
{
	m_goal = new Hex(getHexFromPixelPosition(localPosition.x, localPosition.y));
}

void NavGrid::setGoal(int hx, int hy)
{
	m_goal = new Hex(hx, hy);
}


bool NavGrid::isHexTraversable(Hex hex)
{
	return isHexOnMap(hex) && m_hex[hex]->terrain->isTraversable();
}

//Used for debug editing
void NavGrid::debugMouseInput(sf::Vector2i localPosition) {
	Hex hex = getHexFromPixelPosition(localPosition.x, localPosition.y);
	if(!this->isHexOnMap(hex))
		return;

	updateHexTerrain(hex);
	this->computeDistanceField();
}

//Used for debug editing
void NavGrid::updateHexTerrain(Hex hex) {
	
	Terrain *terrain = m_hex[hex]->terrain;
	switch (terrain->getTerrainType()) {
		case TerrainType_Grass:
			m_hex[hex]->terrain = m_waterTerrain;
			break;
		case TerrainType_Water:
			m_hex[hex]->terrain = m_mountainTerrain;
			break;
		case TerrainType_Mountain:
			m_hex[hex]->terrain = m_grassTerrain;
			break;
		default:
			break;
	}
}

//void HexMap::drawMap(sf::RenderWindow *rw, PathFinder *navGrid, sf::Font *debugFont) {
void NavGrid::drawMap(sf::RenderWindow *rw, sf::Font *debugFont) {

	// REMOVE!
	{
		sf::Text hexText;
		hexText.setFont(*debugFont);
		hexText.setCharacterSize(10);
		hexText.setFillColor(sf::Color::Black);
		hexText.setStyle(sf::Text::Regular);



		for (const std::pair<Hex, HexData*> tile : m_hex)
		{
			Hex hex = tile.first;
			sf::CircleShape terrain = tile.second->terrain->getShape();
			hexText.setString(hex.toString());
			float *pos = getPixelPositionOfHex(hex);

			
			if (hex == Hex(dq,dr))
				terrain.setFillColor(sf::Color::Red);

			Hex* cameFrom = tile.second->m_cameFrom;

			//OutputDebugStringA(( cameFrom->toString() + std::to_string(pos[0]) + "," + std::to_string(pos[1]) + "\n").c_str());



			terrain.setPosition(pos[0], pos[1]);
			rw->draw(terrain);

			hexText.setPosition(pos[0] + m_hexRadius / 2.0f, pos[1] + m_hexRadius / 2.0f);
			rw->draw(hexText);


			if (cameFrom != nullptr) 
			{
				hexText.setString(cameFrom->toString() + " " + std::to_string(tile.second->m_costSoFar));
				hexText.setString(std::to_string(tile.second->m_costSoFar));
				hexText.setPosition(pos[0] + m_hexRadius / 2.0f, pos[1] + m_hexRadius / 2.0f + 20);
				rw->draw(hexText);
			}
		}

		//Draw flow
		for (const std::pair<Hex, HexData*> tile : m_hex)
		{
			Hex hex = tile.first;
			float *pos = getPixelPositionOfHex(hex);
			Hex* cameFrom = tile.second->m_cameFrom;

			if (cameFrom != nullptr)
			{
				float *posCameFrom = getPixelPositionOfHex(*cameFrom);
				sf::Vertex line[2];
				line[0].position = sf::Vector2f(pos[0] + m_hexRadius, pos[1] + m_hexRadius);
				line[0].color = sf::Color::Red;
				line[1].position = sf::Vector2f(posCameFrom[0] + m_hexRadius, posCameFrom[1] + m_hexRadius);
				line[1].color = sf::Color::Red;
				rw->draw(line, 2, sf::Lines);
			}
		}

	}

}

std::string NavGrid::getDebugString()
{	
	std::string map;
	for (const std::pair<Hex, HexData*> tile : m_hex)
	{
		map += (tile.first.toString() +  "\n");
	}
	return map;
}


// 
// Loading And Saving Data Files
//
bool NavGrid::saveMapeToFile(std::string fileName)
{
	// This should come from a config or something
	// --> The path should probably be constructed using a more clever macro/setting
	// Note -> Relative paths start at Skateboards\Source\FiskEngine\FiskEngine (NOT IN SOURCE!)
	std::string navGridDataPath = NAVGRID_DATAPATH + fileName + ".txt";
	const char * testCString = navGridDataPath.c_str();

	//TODO: File must be cleared first

	if (FileManager::fileExists(navGridDataPath.c_str()))
		std::remove(navGridDataPath.c_str());

	//Create new file
	std::fstream file;
	FileManager::createFile(navGridDataPath, file);
	FileManager::openFile(navGridDataPath, file);

	file.clear();

	for (const std::pair<Hex, HexData*> tile : m_hex)
	{
		file << tile.first.x << " " << tile.first.y << " " << tile.first.z << " " << tile.second->terrain->getTerrainType() << std::endl;
	}

	FileManager::closeFile(file);
}

bool NavGrid::loadMap(std::string fileName)
{
	// This should come from a config or something
	// --> The path should probably be constructed using a more clever macro/setting
	// Note -> Relative paths start at Skateboards\Source\FiskEngine\FiskEngine (NOT IN SOURCE!)

	std::string navGridDataPath = NAVGRID_DATAPATH + fileName + ".txt";
	const char * testCString = navGridDataPath.c_str();


	if (!FileManager::fileExists(navGridDataPath.c_str()))
		return false; //Should log error


					  // Open file
	std::fstream file;
	FileManager::openFile(navGridDataPath, file);

	std::string line;

	bool fileLoadedCorrectly = true;


	std::unordered_map<Hex, HexData*> m_hexTemp;
	//m_hex.clear();
	while (std::getline(file, line))
	{

		//			OutputDebugStringA(line.c_str());
		//			OutputDebugStringA(std::string("\n").c_str());

		std::istringstream iss(line);
		int x, y, z, terrainType;
		if (iss >> x >> y >> z >> terrainType)
		{
			Hex h = Hex(x, y, z);
			//Todo: This needs to be done in a better way. Probably need to store terrains in a more data friendly format too so we can load them and not hardcode them.
			switch (terrainType)
			{
			case TerrainType_Grass:
				m_hexTemp.insert({ h, new HexData(m_grassTerrain, &h) });
				break;
			case TerrainType_Mountain:
				m_hexTemp.insert({ h, new HexData(m_mountainTerrain, &h) });
				break;
			case TerrainType_Water:
				m_hexTemp.insert({ h, new HexData(m_waterTerrain, &h) });
				break;
			default:
				//Todo: Error message
				fileLoadedCorrectly = false;
				break;
			}

		}
		else {
			fileLoadedCorrectly = false;
		}
	}


	FileManager::closeFile(file);


	if (fileLoadedCorrectly)
	{
		m_hex.clear();
		m_hex = m_hexTemp;
	}

	computeDistanceField(*m_goal);

	return true;
}