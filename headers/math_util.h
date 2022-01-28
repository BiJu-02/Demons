#pragma once

#include <math.h>

inline int rnd(double x)
{
	double y = int(x);
	y = x - y;
	if (y < 0.5) 
	{ return int(x); }
	return int(x + 1);
}

inline double sq_dist(double x1, double y1, double x2, double y2)
{ return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1); }

inline double dist(double x1, double y1, double x2, double y2)
{ return sqrt(sq_dist(x1, y1, x2, y2)); }

