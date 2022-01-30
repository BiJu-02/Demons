#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>
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
	bool in_game, is_playing, is_paused;

	Map map;
	SDL_Texture* map_tex;
	
	std::list<Game_Obj*> sprite_list;

	int max_heroes = 6, no_of_heroes;
	Game_Obj* hero_arr[6];
	int slot = -1;

	std::vector<int> enemy_batch;
	int batch_size, wave_no;
	double spawn_tm_intrvl = 4, spawn_tm_qtm = 0.017;
	bool enemy_on_map;

	int score;
	int lives;
	int coins;

	World();
	void start_game();
	void update();
	void spawn_enemy();
	void sprite_list_trav();
	void decr_life(int id);
	void sprite_create();
	void sprite_destroy();
	void exit_game();
};