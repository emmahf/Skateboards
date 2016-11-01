#pragma once

// Temp struct - cubic coordinates
struct Hex
{	
	const int x;
	const int y;
	const int z;
	Hex(int x_, int y_, int z_) : x(x_), y(y_), z(z_) {}
	Hex(int x_, int y_) : x(x_), y(y_), z(-x_ - y_) {}
};

