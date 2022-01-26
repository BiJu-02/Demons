#pragma once

class Game_Obj
{
public:
	bool is_active;
	int xscrn, yscrn;		// cntre coordinate of sprite on screen (des_rec
	int x3d, y3d, z3d;		// 3d coordinates
	int xend, yend;
	double vx, vy, vz, vxy, az;
	double tm_cur, tm_prd, tm_qtm = 0.05;

	Game_Obj(int x, int y);
};
