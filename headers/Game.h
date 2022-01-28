#pragma once

#include "World.h"


//int screen 
//0 -> start
//1 -> pre playing
//2 -> playing map
//3 -> paused map
//4 -> credits
//5 -> score, name input and save
//6 -> leaderboard

//int slot
//-1 -> none selected
//0 to 5 -> one of the heores in hero_arr

//bool misc_render[10]
//0:start screen, 
//1:hud, 
//2:hero slots, 
//3:character stats, 
//4:hero types, 
//5:lvl up/skill?, 
//6:paused transparent shade, 
//7:quit confirm, 
//8:enter name and save, 
//9:leaderboard


class Game
{
public:
	SDL_Window* win;
	SDL_Renderer* ren;
	TTF_Font* font;
	SDL_Event event;
	SDL_Rect src_rec, des_rec;

	Uint64 frame_time, frame_delay;

	bool is_running;
	int screen;
	int slot = -1;

	SDL_Texture* sprite_tex[6];		// according to tex_id in Game_Obj
	SDL_Texture* misc_tex[10];
	bool misc_render[10];

	World wrld;

	Game(const char *title, int x, int y, int w, int h, int sc, int fps);
	void loop();
	void handle_event();
	void update();
	void render();
	void set_misc_render();
	void clean();
	SDL_Texture* load_texture(const char* img_path);
	void handle_start_screen(int x, int y);		// start and cred button
	void handle_game_screen1(int x, int y);		// pre playing...no enemies spawning, can interact with hero slot and hero position
	void handle_game_screen2(int x, int y);		// enemies spawning and following path, can interact with hero slot and hero position, can interact with play/pause butt
	void handle_game_screen3(int x, int y);		// all game loop stops...can onli interact with play/pause butt
	void handle_score_screen();					// might need keyboard input also...
};

