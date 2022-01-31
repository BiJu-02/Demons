#pragma once

#include "World.h"


//int screen 
//0 -> start
//1 -> game
//2 -> credits
//3 -> score, name input and save, leaderboard

//int slot
//-1 -> none selected
//0 to 5 -> one of the heores in hero_arr

//bool misc_render[10]
//0:start screen, 
//1:hud, 
//2:character stats, 
//3:hero types, 
//4:lvl up, 
//5: hero selection
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
	
	SDL_Texture* icons;


	SDL_Texture* sprite_tex[6];		// according to tex_id in Game_Obj
	SDL_Texture* misc_tex[10];
	bool misc_render[10];


// ####################################
	std::string curr_plyr_name;
	std::string ldr_brd_names[5];
	int ldr_brd_scores[5];
	bool cur_score_greater;
	int no_of_plyrs;
	//wrld.score....DO NOT REWRITE




// #########################################

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
	void handle_game_screen(int x, int y);

	void render_game_screen();


// ##############################
	void handle_score_screen();	
	void render_score_screen();


// ##############################
};

 