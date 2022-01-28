#pragma once

#include <iostream>
#include <list>
#include <vector>
#include <algorithm>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Map.h"
#include "Game_Obj.h"


//typedef struct
//{
//	Game_Obj* obj;
//	SDL_Rect obj_srec, obj_drec;
//} sprite;


// load all sprite textures in constructors ...you only need to pass rects to rendercopy for multiple of them
// 0:enemy1, 1:enemy2, 2:enemy3, 3:hero1,  4:hero2, 5:hero3, 6:proj1, 7:proj2

class World
{
public:
	bool is_playing, in_game;

	Map map;
	SDL_Texture* map_tex;
	SDL_Texture *sprite_tex[8];		
	std::list<Game_Obj*> sprite_list;
	int max_heroes, num_of_heroes;
	Game_Obj* hero_arr[6];
	std::vector<int> enemy_batch;
	int batch_size, wave_no;

	int score;
	int lives;
	int coins;

	World();
	void update();
	void sprite_create();
	void sprite_destroy();
};