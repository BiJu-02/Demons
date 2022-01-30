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
	virtual void set_dest(int x, int y, int face) {}
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
};


class Enemy : public Character
{
public:
	int *path_x, *path_y;
	int chk_pts, cur_chk_pt;
	int kill_reward;
	int temp_face;

	Enemy(int x, int y, int z, int w, int h, std::string& nm, int tx_id, int* pth_x, int* pth_y, int cp);
	void update();
	void set_path();
};

class Hero : public Character
{
public:
	double heal_rate, revival_tm;

	Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id);
	void set_dest(int x, int y, int face);
	void set_camp(int x, int y);
};