#include "PathFinder.h"



PathFinder::PathFinder(NavGrid *map, Hex destination) {
	//m_goal = Hex(destination.x, destination.y);

	for (const std::pair<Hex, HexData*> tile : *map->getHexes())
	{
		NavData *basic = new NavData();
		const Hex h = Hex(tile.first);
		m_navGrid.insert({ h, basic });
	}

	m_frontier.push(destination);


	while (!m_frontier.empty())
	{
		Hex currentHex = m_frontier.front();
		std::vector<Hex> neighbours = currentHex.getNeighbours(currentHex);

		for (auto neighbour : neighbours)
		{
			if (map->isHexOnMap(neighbour) && m_navGrid[neighbour]->m_cameFrom == nullptr)
			{
				m_navGrid[neighbour]->m_cameFrom = &currentHex;
				m_frontier.push(neighbour);
			}
		}

		m_frontier.pop();
	}
}


PathFinder::~PathFinder()
{
}
