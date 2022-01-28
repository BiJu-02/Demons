#include "World.h"

World::World() : map(Map("map"))
{
	// load map first; get path instructions, base coins, base lives
	// set score to 0
	// load all sprite textures

	// temporary shit
	//is_playing = true;
	//std::string s = "min";
	//sprite_list.emplace_front(new Enemy(50, 520, 0, 80, 80, s, 0, map.path_instruct_x, map.path_instruct_y, map.map_chk_pts));
}

// at the end of updates sort the forward list of sprites
void World::update()
{
	for (auto sprite : sprite_list)
	{ sprite->update(); }

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

 