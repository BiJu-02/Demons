#include "World.h"

World::World() : map(Map("map"))
{
	// load map first; get path instructions, base coins, base lives
	// set score to 0
	// load all sprite textures

}

// at the end of updates sort the forward list of sprites
void World::update()
{
	if (lives == 0)
	{ in_game = false; }
	sprite_list.sort([](Game_Obj* a, Game_Obj* b) { return a->yscrn < b->yscrn; });
}

void World::sprite_create()
{

}

void World::sprite_destroy()
{

}

 