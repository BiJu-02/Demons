#pragma once

#include "World.h"

class Game
{
public:
	SDL_Window* win;
	SDL_Renderer* ren;
	TTF_Font* font;
	SDL_Event event;
	bool is_running, is_playing;
	Uint64 frame_time, frame_delay;
	World wrld;

	Game(const char *title, int x, int y, int w, int h, int sc, int fps);
	void loop();
	void handle_event();
	void update_render();
	void clean();
};

