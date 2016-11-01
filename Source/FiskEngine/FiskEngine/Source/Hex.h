#pragma once
#include <string>

// Temp struct (cubic coordinates)
struct Hex
{	
	const int x;
	const int y;
	const int z;
	Hex(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
	Hex(int x_, int y_) : x(x_), y(y_), z(-x_ - y_) {}

	bool operator== (const Hex& h) const { return(x == h.x && y == h.y); }

	std::string  toString() const { return ("hex(" + std::to_string(x) + "," + std::to_string(y) + ")"); }

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