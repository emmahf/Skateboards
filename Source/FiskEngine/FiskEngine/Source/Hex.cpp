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

std::vector<Hex> Hex::getNeighbours(Hex hex)
{
	std::vector<Hex> n;
	for (int i = 0; i < 6; i++) {
		n.push_back(getNeighbour(hex, i));
	}
	return n;
}

void Hex::cubicRound(float &q_, float &r_, float &s_)
{	

	q_ = floor(q_);
	r_ = floor(r_);
	s_ = -q_ - r_;
	/*
	int q = int(floor(q_));
	int r = int(floor(r_));
	int s = int(floor(s_));

	double q_diff = abs(q - q_);
	double r_diff = abs(r - r_);
	double s_diff = abs(s - s_);

	if (q_diff > r_diff && q_diff > s_diff)
	{
		q = -r - s;
	}
	else if (r_diff > s_diff)
	{
		r = -q - s;
	}
	else
	{
		s = -q - r;
	}

	q_ = q;
	r_ = r;
	s_ = s;
	*/
}
