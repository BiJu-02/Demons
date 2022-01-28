#include "Game_Obj.h"
#include "math_util.h"


Game_Obj::Game_Obj(int x, int y, int z, int w, int h, std::string& nm, int tx_id)
{
	xscrn = x3d = x;
	z3d = z;
	y3d = y;
	yscrn = rnd(y - z / 1.7320508076);
	width = w;
	height = h;
	name = nm;
	tex_id = tx_id;
}

void Character::set_dest(int x, int y, int face)
{
}

Character::Character(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Game_Obj(x, y, z, w, h, nm, tx_id)
{
}

Hero::Hero(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Character(x, y, z, w, h, nm, tx_id)
{
}

Enemy::Enemy(int x, int y, int z, int w, int h, std::string& nm, int tx_id) : Character(x, y, z, w, h, nm, tx_id)
{

}
