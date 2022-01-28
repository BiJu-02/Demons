#pragma once
#include <string>

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
	bool is_active, is_moving;
	int src_x, src_y, src_w, src_h;
	int width, height;
	int xscrn, yscrn;		// centre coordinate of sprite along its width on screen (drec.x + drec.w / 2, drec.y + height)
	int x3d, y3d, z3d;		// 3d coordinates
	int xend, yend;			// destination coordinates if the object is moving
	double vx, vy, vz, vxy, az;
	double tm_cur, tm_prd, tm_qtm = 0.05;
	std::string name;
	int tex_id;

	Game_Obj(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
};

//facing:
//0 -> left
//1 -> right
//2 -> front (showing us the back side)
//3 -> back (showing us the front side)
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
	int hp, atk;
	int facing, action;
	//double 

	Character(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	virtual void update() {}
	void set_dest(int x, int y, int face);
};

class Hero : public Character
{
public:
	double heal_rate, revival_tm;

	Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
};

class Enemy : public Character
{
public:
	int* path;
	int kill_reward;

	Enemy(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
};
