#pragma once

#include <unordered_set>
#include <unordered_map>
#include <queue>
#include "hexMap.h"

struct Path {


};

struct NavData {
	
	bool m_visited;
	double m_movementCost;
	Hex* m_cameFrom;

	NavData() : m_visited(false), m_movementCost(1), m_cameFrom(nullptr) {};

};

class PathFinder
{

public:
	PathFinder(NavGrid *map, Hex destination);

	~PathFinder();

	Hex* getCameFrom(const Hex h) {
		return m_navGrid[h]->m_cameFrom;
	};

	static Path* MapDistance(NavGrid *map, Hex destination) {


	}

private:

	mutable std::unordered_map<Hex, NavData*> m_navGrid;
	Hex m_goal;

	std::queue<Hex> m_frontier;
	std::vector<Hex> m_test;

};

