#include "Game_Obj.h"



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



Character::Character(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Game_Obj(x, y, z, w, h, nm, tx_id)
{
}

void Character::set_src()
{
	is_ded = false;
	// for source rect of charactes using action and facing

}

bool Character::in_fight()
{
	return target.empty();
}

void Character::set_target(Game_Obj* t)
{
	target.push_back(t);
}

Hero::Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Character(x, y, z, w, h, nm, tx_id)
{
	camp_x = x;
	camp_y = y;
	lvl = 1;
	is_moving = false;
}


void Hero::set_camp(int x, int y)
{
	release_targets();
	camp_x = x;
	camp_y = y;
	to_camp = true;
	at_camp = false;
	to_enemy = false;
	set_dest(x, y);
}

void Hero::lvl_up()
{
}

void Hero::set_target(Game_Obj* t)
{
	if (!target.empty()) 
	{ target.clear(); }
	target.push_back(t);
}

Game_Obj* Hero::get_target()
{
	if (target.empty())
	{ return NULL; }
	return target.back();
}

void Hero::remove_target(Game_Obj* t = NULL)
{
	target.clear();
}

bool Hero::ready_to_fight()
{
	return in_stance;
}

void Melee::release_targets()
{
	Game_Obj* temp = target.back();
	target.clear();
	temp->remove_target(this);
}

Melee::Melee(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Hero(x, y, z, w, h, nm, tx_id)
{
	rev_tmr = 0;
	revival_tm = 7;
	at_camp = true;
	to_enemy = false;
	to_camp = false;
	in_stance = false;
}

void Melee::update()
{
	if (hp < 1)
	{
		is_ded;
		src_x = 0;
		src_y = 0;
		hp = max_hp;
		return;
	}
	if (is_ded)
	{
		if (rev_tmr > revival_tm)
		{
			rev_tmr = 0;
			is_ded = false;
		}
		else
		{
			rev_tmr += 0.017;
		}
		return;
	}
	if (hp < max_hp)
	{
		hp += 0.017;
	}
	if (is_moving)
	{
		if (tm_cur > tm_prd)
		{
			is_moving = false;
			if (to_enemy)
			{
				to_enemy = false;
				in_stance = true;
			}
			else
			{
				to_camp = false;
				at_camp = true; 
			}
			return;
		}
		tm_cur += tm_qtm;
		x2d = xi + vx * tm_cur;
		y2d = yi + vy * tm_cur;
		if (int(tm_cur * 100) % 3 == 0)
		{ action = (action + 1) % 3; }
		xscrn = x2d - wscrn / 2;
		yscrn = y2d - hscrn;
		return;
	}
	if (in_fight())
	{
		if (in_stance)		// fighting
		{

		}
		else				// need to move to enemy...
		{
			to_enemy = true;
			at_camp = false;
			set_dest(target.back()->x2d + target.back()->wscrn / 2, target.back()->y2d);
		}

	}
	else
	{
		if (!at_camp)		// moving back to camp point
		{
			to_camp = true;
			set_dest(camp_x, camp_y);
		}
	}
}

void Melee::set_dest(int x, int y)
{
	tm_cur = 0;
	tm_prd = dist(x2d, y2d, x, y) / vxy;
	ang = atan2(y - y2d, x - x2d);
	vx = vxy * cos(ang);
	vy = vxy * sin(ang);
	xi = x2d;
	yi = y2d;
	is_moving = true;
}

Range::Range(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Hero(x, y, z, w, h, nm, tx_id)
{
	// "range"
}

void Range::update()
{
	// either fighting or not...
	if (in_fight())
	{
		if (dist(x2d, y2d, target.back()->x2d, target.back()->x3d) < 200)
		{
			// phat se headshot
		}
		else
		{ target.clear(); }
	}
	// else nothing...?
}

void Range::set_dest(int x, int y)
{
	x2d = x;
	y2d = y;
	xscrn = x2d - wscrn / 2;
	yscrn = y2d - hscrn;
}



Enemy::Enemy(int x, int y, int z, int w, int h, std::string& nm, int tx_id, int *pth_x, int *pth_y, int cp) : Character(x, y, z, w, h, nm, tx_id)
{
	path_x = pth_x;
	path_y = pth_y;
	chk_pts = cp;		
	cur_chk_pt = 0;
	is_moving = true;
	is_active = true;
	// set facing and action too
	src_x = src_y = 0;
	src_w = src_h = 80;
		// stats and kill reward, kinematic variables,
	hp = 100 + tx_id * 0.5;
	atk = 10 + tx_id * 10;
	kill_reward = 1 + tx_id * 10;
	vxy = 40 - tx_id * 0.1;
	set_path();
	action = 0;
}

void Enemy::update()
{
	if (hp < 1)
	{
		is_active = false; 
		is_ded = true;
		return;
	}
	if (in_fight())
	{
		//fight
		Game_Obj* temp = target.front();
		if (temp->ready_to_fight())
		{

		}

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
		xscrn = x2d - wscrn / 2;
		yscrn = y2d - hscrn;
	}
	
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

void Enemy::remove_target(Game_Obj* t = NULL)
{
	target.remove(t);
}

void Enemy::release_targets()
{
	Game_Obj* temp;
	std::list<Game_Obj*>::iterator iter = target.begin();
	std::list<Game_Obj*>::iterator end = target.end();
	while (iter != end)
	{
		temp = *iter;
		iter = target.erase(iter);
		temp->remove_target(this);
	}
}


