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
	//is_ded = false;
	// for source rect of charactes using action and facing
	if (is_ded)
	{
		src_x = 0;
		src_y = 0;
	}
	src_y = facing * 80;
	src_x = action * 80;
}

bool Character::in_fight()
{
	return !target.empty();
}

void Enemy::set_target(Game_Obj* t)
{
	target.push_back(t);
}

Hero::Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Character(x, y, z, w, h, nm, tx_id)
{
	src_x = 0;
	src_y = 160;
	src_w = w;
	src_h = h;
	camp_x = x;
	camp_y = y;
	lvl = 1;
	is_moving = false;
	facing = 2;
}

int Hero::get_lvl()
{
	return lvl;
}


void Melee::set_camp(int x, int y)
{
	release_targets();
	camp_x = x;
	camp_y = y;
	to_camp = true;
	at_camp = false;
	to_enemy = false;
	in_stance = false;
	std::cout << "good 1" << std::endl;
	set_dest(x, y);
}

void Hero::lvl_up()
{
	lvl++;
	atk += lvl * 10;
	hp += lvl * 100;
}

void Melee::set_target(Game_Obj* t)
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
	if (!target.empty())
	{ target.clear(); }
}

bool Melee::ready_to_fight()
{
	return in_stance;
}

void Character::dec_hp(int a)
{
	hp -= a;
}

void Melee::release_targets()
{
	if (!target.empty())
	{
		Game_Obj* temp = target.back();
		target.clear();
		temp->remove_target(this);
	}
}

Melee::Melee(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Hero(x, y, z, w, h, nm, tx_id)
{
	hp = max_hp = 200;
	atk = 10;
	vxy = 60;
	heal_rate = 1;
	rev_tmr = 0;
	revival_tm = 7;
	is_active = true;
	at_camp = true;
	to_enemy = false;
	to_camp = false;
	in_stance = false;
	atk_tmr = 0;
}

void Melee::update()
{
	if (hp < 1)
	{
		is_ded = true;
		src_x = 0;
		src_y = 0;
		hp = max_hp;
		rev_tmr = 0;
		in_stance = false;
		release_targets();
		action = 0;
		facing = 0;
		return;
	}
	if (is_ded)
	{
		if (rev_tmr > revival_tm)
		{
			rev_tmr = 0;
			is_ded = false;
			at_camp = true;
			to_enemy = false;
			to_camp = false;
			xscrn = camp_x - wscrn / 2;
			yscrn = camp_y - hscrn;
			action = 0;
			facing = 2;
		}
		else
		{
			rev_tmr += 0.017;
		}
		return;
	}
	if (hp < max_hp)
	{
		hp += 0.017 * heal_rate;
	}
	if (is_moving)
	{
		//std::cout << "good bhai good" << std::endl;
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
		if (int(tm_cur * 100) % 13 == 0)
		{
			action = (action + 1) % 3;
			if (action == 0) { action = 1; }
		}
		xscrn = x2d - wscrn / 2;
		yscrn = y2d - hscrn;
		set_src();
		return;
	}
	if (in_fight())
	{
		if (in_stance)		// fighting
		{
			if (atk_tmr > 0.99)
			{
				atk_tmr = 0;
				target.back()->dec_hp(atk);
			}
			else
			{
				atk_tmr += 0.017;
				if (atk_tmr < 0.33)
				{ action = 0; }
				else if (atk_tmr < 0.66)
				{ action = 3; }
				else
				{ action = 4; }
			}
		}
		else				// need to move to enemy...
		{
			to_enemy = true;
			at_camp = false;
			set_dest(target.back()->x2d + target.back()->wscrn / 2, target.back()->y2d);
		}
		facing = 2;
	}
	else
	{
		if (!at_camp)		// moving back to camp point
		{
			to_camp = true;
			set_dest(camp_x, camp_y);
		}
		else
		{
			action = 0;
			facing = 2;
		}
	}
	set_src();
}

void Melee::set_dest(int x, int y)
{
	tm_cur = 0;
	tm_prd = dist(x2d, y2d, x, y) / vxy;
	ang = atan2(y - y2d, x - x2d);
	vx = vxy * cos(ang);
	vy = vxy * sin(ang);
	// set face using ang...?
	if (1.396263 <= ang && ang <= 1.919862)
	{ facing = 0; }
	else if (-1.919862 <= ang && ang <= -1.396263)
	{ facing = 3; }
	else if (-1.396263 < ang && ang < 1.396263)
	{ facing = 1; }
	else
	{ facing = 2; }
	xi = x2d;
	yi = y2d;
	is_moving = true;
	std::cout << "good 2" << std::endl;
}

Range::Range(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Hero(x, y, z, w, h, nm, tx_id)
{
	// "range"
	is_active = true;
	hp = 100;
	atk = 10;
	atk_tmr = 1;
}

void Range::update()
{
	// either fighting or not...
	if (in_fight())
	{
		double dis = dist(x2d, y2d, target.back()->x2d, target.back()->y2d);

		if (dis < 200)
		{
			// phat se headshot
			if (atk_tmr > 1)
			{
				atk_tmr = 0;
				rasengan = true;			// set a flag to initialize blue ball
			}
			else
			{
				atk_tmr += 0.017;
				
				if (atk_tmr < 0.33)
				{ action = 0; }
				else if (atk_tmr < 0.66)
				{ action = 3; }
				else
				{ action = 4; }
			}
		}
		else
		{ target.clear(); }		// after it goes out of range
	}
	// else nothing...?
	set_src();
}

void Range::set_camp(int x, int y)
{
	x2d = x;
	y2d = y;
	xscrn = x2d - wscrn / 2;
	yscrn = y2d - hscrn;
}

void Range::set_target(Game_Obj* t)
{
	if (!target.empty()) 
	{ target.clear(); }
	target.push_back(t);
	atk_tmr = 0;
}

bool Range::is_blast()
{
	return rasengan;
}

void Range::blast_done()
{
	rasengan = false;
}

int Character::get_atk()
{
	return atk;
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
	src_x = 0;
	src_y = 80;
	src_w = src_h = 80;
		// stats and kill reward, kinematic variables,
	hp = 100 + tx_id * 0.5;
	atk = 10 + tx_id * 10;
	kill_reward = 10 + tx_id * 10;
	vxy = 30 - tx_id * 0.1;
	set_path();
	action = 1;
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
			if (atk_tmr > 0.99)
			{ 
				atk_tmr = 0;
				temp->dec_hp(atk);
			}
			else
			{
				atk_tmr += 0.017;
				if (atk_tmr < 0.33)
				{ action = 0; }
				else if (atk_tmr < 0.66)
				{ action = 3; }
				else
				{ action = 4; }
			}
		}
		else
		{
			// wet action
			action = 0;
		}
		facing = 1;
		set_src();
		return;
	}
	if (is_moving)
	{
		if (tm_cur < tm_prd)
		{
			tm_cur += tm_qtm;
			x2d = xi + rnd(vx * tm_cur);
			y2d = yi + rnd(vy * tm_cur);
			if (int(tm_cur * 100) % 13 == 0)
			{ 
				action = (action + 1) % 3;
				if (action == 0) { action = 1; }
			}
			//std::cout << action << std::endl;
		}
		else
		{
			set_path();
		}
		xscrn = x2d - wscrn / 2;
		yscrn = y2d - hscrn;
		set_src();
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
	if (1.396263 <= ang && ang <= 1.919862)
	{ facing = 0; }
	else if (-1.919862 <= ang && ang <= -1.396263)
	{ facing = 3; }
	else if (-1.396263 < ang && ang < 1.396263)
	{ facing = 1; }
	else
	{ facing = 2; }
	cur_chk_pt++;
	//std::cout << cur_chk_pt << std::endl;
}

void Enemy::set_range_target(Game_Obj* t)
{
	range_target.push_back(t);
}

void Enemy::remove_target(Game_Obj* t = NULL)
{
	target.remove(t);
}

void Enemy::release_targets()
{
	Game_Obj* temp;
	while (target.begin() != target.end())
	{
		temp = target.back();
		target.pop_back();
		temp->remove_target(this);
	}
	while (range_target.begin() != range_target.end())
	{
		temp = range_target.back();
		range_target.pop_back();
		temp->remove_target(this);
	}
	
}

void Enemy::about_to_fight()
{
	//action
}

Projectile::Projectile(int x, int y, int z, int w, int h, std::string& nm, int tx_id, Game_Obj* shtr) : Game_Obj(x, y, z, w, h, nm, tx_id)
{
	src_x = 0; src_y = 0;
	src_w = 40; src_h = 40;
	is_active = true;
	shooter = shtr;
	Game_Obj* temp = shtr->get_target();
	// set speed and tmr
	vxy = 150;
	tm_cur = 0;
	tm_prd = dist(x, y, temp->x2d, temp->y2d - temp->hscrn) / vxy;
	ang = atan2((temp->y2d - 40) - y, temp->x2d - x);
	vx = vxy * cos(ang);
	vy = vxy * sin(ang);
}

void Projectile::update()
{
	// direct tmr condition
	if (tm_cur > tm_prd)
	{
		is_active = false;
		// access target of shooter is still a target and dec hp by shooters atk
		if (shooter->in_fight())
		{
			Game_Obj* temp = shooter->get_target();
			temp->dec_hp(shooter->get_atk());
		}
	}
	else
	{
		tm_cur += tm_qtm;
		x2d = xi + rnd(vx * tm_cur);
		y2d = yi + rnd(vy * tm_cur);
		xscrn = x2d - wscrn / 2;
		yscrn = y2d - hscrn;
	}

}
