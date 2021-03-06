#pragma once
#include <string>
#include "terrain.h"
#include "assert.h"
// Temp struct (cubic coordinates)
// Many options, could
// 1. Use array instead -> easier function
// 2. math library with vec3 : don't need to define add/subtract functions etc + get matrix ops. 
// 3. template this a bit so we could use same structure for fractional hexes (do we need frac hex?) 

struct Hex
{
	const int x;
	const int y;
	const int z;
	Hex() : x(0), y(0), z(0) { assert(x + y + z == 0); } //default constructor
	Hex(int x_, int y_, int z_) : x(x_), y(y_), z(z_) { assert(x + y + z == 0); } //cubic constructor
	Hex(int x_, int y_) : x(x_), y(y_), z(-x_ - y_) { assert(x + y + z == 0); } //axial constructor

	// Todo: fix
	int distance(Hex a, Hex b) { return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) / 2; }
	//sf::Vector2f direction(Hex a, Hex b) { return (abs(a.x - b.x) + abs(a.y - b.y) + abs(a.z - b.z)) / 2; }

	Hex getDirection(int dir);
	Hex getNeighbour(Hex hex, int dir);
	std::vector<Hex> getNeighbours(Hex hex);

	Hex hexAdd(Hex a, Hex b) { return Hex(a.x + b.x, a.y + b.y, a.z + b.z); }
	Hex hexSub(Hex a, Hex b) { return Hex(a.x - b.x, a.y - b.y, a.z - b.z); }
	Hex hexMultiply(Hex a, int k) { return Hex(a.x * k, a.y * k, a.z * k); }
	
	// Todo: Implement proper ways of getting different coordinates so this can be done better
	static void cubicRound(float &q_, float &r_, float &s_);

	bool operator== (const Hex& h) const { return(x == h.x && y == h.y); }
	bool operator!= (const Hex& h) const { return !(x == h.x && y == h.y);}
	//Hex  operator= (const Hex& h) { return *this; }


	std::string  toString() const { return ("hex(" + std::to_string(x) + "," + std::to_string(y) + ")"); }

	static const Hex directions[];
};

namespace std
{
	template <>
	struct hash<Hex>
	{
	  
		size_t operator()(Hex const & hex) const noexcept
		{
			return ((51 + std::hash<int>()(hex.x)) * 51 + std::hash<int>()(hex.y));
		}
	};


}