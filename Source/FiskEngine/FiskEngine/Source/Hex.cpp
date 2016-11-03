#include "Hex.h"

const Hex Hex::directions[] = { Hex(1, 0, -1), 	Hex(1, -1, 0), 	Hex(0, -1, 1),	Hex(-1, 0, 1), 	Hex(-1, 1, 0), 	Hex(0, 1, -1) };

Hex Hex::getDirection(int dir)
{
	return directions[(6 + (dir % 6)) % 6];
}

Hex Hex::getNeighbour(Hex hex, int dir)
{
	return hexAdd(hex, getDirection(dir));
}
