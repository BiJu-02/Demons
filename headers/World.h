#pragma once


#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Map.h"
#include "Game_Obj.h"



class World
{
public:
	bool in_game, is_playing, is_paused;

	Map map;
	SDL_Texture* map_tex;
	
	std::list<Game_Obj*> sprite_list;

	int max_heroes = 6, no_of_heroes;
	Game_Obj* hero_arr[6];
	int slot;

	std::vector<int> enemy_batch;
	int batch_size, wave_no;
	double spawn_tm_intrvl = 4, spawn_tm_qtm = 0.017;
	bool enemy_on_map;

	int score;
	int lives;
	int coins;

	std::string enemy = "enemy", melee = "melee", range = "range", proj = "proj";

	World();
	void start_game();
	void update();
	void spawn_enemy();
	void spawn_melee();
	void spawn_range();
	void sprite_list_trav();
	void decr_life(int id);
	void sprite_create();
	void sprite_destroy();
	void exit_game();
};