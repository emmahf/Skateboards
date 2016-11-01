#include "hexMap.h"
#include <string>


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
