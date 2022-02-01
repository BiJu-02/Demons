#pragma once
#include <iostream>
#include <string>
#include <list>

#include "math_util.h"

//tex_id:
//0 -> low enemy
//1 -> mid enemy
//2 -> boss
//3 -> melee hero
//4 -> ranged hero
//5 -> projectile

class Game_Obj
{
public:
	bool is_active, is_moving, is_ded = false;
	bool enemy_passed = false;
	int src_x, src_y, src_w, src_h;
	int wscrn, hscrn;
	int xscrn, yscrn;		// centre coordinate of sprite along its width on screen (drec.x + drec.w / 2, drec.y + height)
	int x3d, y3d, z3d;		// 3d coordinates
	int xi, yi, zi;
	int x2d, y2d;
	int xend, yend;			// destination coordinates if the object is moving
	double vx, vy, vz, vxy, az;
	double tm_prd, tm_cur = 0, tm_qtm = 0.05;
	double ang;
	std::string name;
	int tex_id;

	Game_Obj(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	virtual void update() {}
	virtual void set_camp(int x, int y) {}
	virtual void set_dest(int x, int y) {}
	virtual int get_reward() { return NULL; }
	virtual void set_target(Game_Obj* t) {}
	virtual void set_range_target(Game_Obj* t) {}
	virtual Game_Obj* get_target() { return NULL; }
	virtual void release_targets() {}
	virtual void remove_target(Game_Obj* t) {}
	virtual void about_to_fight() {}		// set action and face
	virtual bool ready_to_fight() { return false; }
	virtual bool in_fight() { return false; }
	virtual void dec_hp(int a) {}
	virtual bool is_blast() { return false; }
	virtual void blast_done() {}
	virtual int get_atk() { return NULL; }
	virtual int get_lvl() { return NULL; }
	virtual void lvl_up() {}
};

//facing:
//0 -> back (showing us the front side)
//1 -> right
//2 -> left
//3 -> front (showing us the back side)
//
//action:
//0 -> standing
//1 -> left foot forward (walking)
//2 -> right foot forward (walking)
//3 -> about to attack
//4 -> attacked

class Character : public Game_Obj
{
public:
	int hp, atk, max_hp;
	int facing, action;
	double atk_tmr;
	//double 
	std::list<Game_Obj*> target;

	Character(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	void set_src();
	bool in_fight();
	void dec_hp(int a);
	int get_atk();
};


class Enemy : public Character
{
public:
	int *path_x, *path_y;
	int chk_pts, cur_chk_pt;
	int kill_reward;
	int temp_face;

	std::list<Game_Obj*> range_target;

	Enemy(int x, int y, int z, int w, int h, std::string& nm, int tx_id, int* pth_x, int* pth_y, int cp);
	void update();
	void set_path();
	int get_reward() { return kill_reward; }
	void set_target(Game_Obj* t);
	void set_range_target(Game_Obj* t);
	void remove_target(Game_Obj* t);
	void release_targets();			// can have multiple targets
};

class Hero : public Character
{
public:
	int camp_x, camp_y;
	int lvl;
	bool in_stance, at_camp, to_enemy, to_camp;

	Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	int get_lvl();
	void lvl_up();
	Game_Obj* get_target();
	void remove_target(Game_Obj* t);
};

class Melee : public Hero
{
public:
	double heal_rate, revival_tm;
	double rev_tmr;
	

	Melee(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	void update();
	void set_camp(int x, int y);
	void set_dest(int x, int y);
	void set_target(Game_Obj* t);
	void release_targets();			// hero will always only have 1 target
	bool ready_to_fight();
};

class Range : public Hero
{
public:
	bool rasengan;
	double proj_tm_prd, proj_tmr;

	Range(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	void update();
	void set_camp(int x, int y);
	void set_target(Game_Obj* t);
	bool is_blast();
	void blast_done();
};

class Projectile : public Game_Obj
{
public:
	Game_Obj* shooter;

	Projectile(int x, int y, int z, int w, int h, std::string& nm, int tx_id, Game_Obj* shtr);
	void update();
};