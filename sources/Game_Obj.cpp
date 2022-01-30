#include "Game_Obj.h"
#include "math_util.h"
#include <iostream>


Game_Obj::Game_Obj(int x, int y, int z, int w, int h, std::string& nm, int tx_id)
{
	xi = x2d = x3d = x;
	z3d = z;
	y3d = y;
	yi = y2d = rnd(y - z / 1.7320508076);
	wscrn = w;
	hscrn = h;
	xscrn = x - w / 2;
	yscrn = y - h;
	name = nm;
	tex_id = tx_id;
}

void Hero::set_dest(int x, int y, int face)
{
}

void Hero::set_camp(int x, int y)
{
}

Character::Character(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Game_Obj(x, y, z, w, h, nm, tx_id)
{
}

Hero::Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Character(x, y, z, w, h, nm, tx_id)
{
}

Enemy::Enemy(int x, int y, int z, int w, int h, std::string& nm, int tx_id, int *pth_x, int *pth_y, int cp) : Character(x, y, z, w, h, nm, tx_id)
{
	path_x = pth_x;
	path_y = pth_y;
	chk_pts = cp;		
	cur_chk_pt = 0;
	is_moving = true;
	is_active = true;
	src_x = src_y = 0;
	src_w = src_h = 80;
		// stats and kill reward, kinematic variables,
	hp = 100 + tx_id * 0.5;
	atk = 10 + tx_id * 10;
	kill_reward = 1 + tx_id;
	vxy = 40 - tx_id * 0.1;
	set_path();
	action = 0;
}

void Enemy::update()
{
	if (hp < 1)
	{
		is_active = false; 
		return;
	}
	if (is_moving)
	{
		if (tm_cur < tm_prd)
		{
			tm_cur += tm_qtm;
			x2d = xi + rnd(vx * tm_cur);
			y2d = yi + rnd(vy * tm_cur);
			if (int(tm_cur * 100) % 3 == 0)
			{ action = (action + 1) % 3; }
			//std::cout << action << std::endl;
		}
		else
		{
			set_path();
		}
	}
	else
	{
		// fighting
	}
	xscrn = x2d - wscrn / 2;
	yscrn = y2d - hscrn;
}

inline void Enemy::set_path()
{
	if (cur_chk_pt == chk_pts)
	{
		is_moving = false;
		is_active = false;
		enemy_passed = true;
	}
	tm_cur = 0;
	// from path calculate next time period and vx and vy
	tm_prd = dist(x2d, y2d, path_x[cur_chk_pt], path_y[cur_chk_pt]) / vxy;
	ang = atan2(path_y[cur_chk_pt] - y2d, path_x[cur_chk_pt] - x2d);
	//std::cout << ang << std::endl;
	vx = vxy * cos(ang);
	vy = vxy * sin(ang);
	xi = x2d;
	yi = y2d;
	cur_chk_pt++;
	//std::cout << cur_chk_pt << std::endl;
}


