#include "Game.h"


Game::Game(const char* title, int x, int y, int w, int h, int sc, int fps) : wrld(World())
{
	if (!SDL_Init(SDL_INIT_EVERYTHING))
	{
		std::cout << "SDL initialized" << std::endl;

		win = SDL_CreateWindow(title, x, y, w, h, sc);
		if (win)
		{ std::cout << "Window created" << std::endl; }
		else { exit(1); }

		ren = SDL_CreateRenderer(win, -1, sc);
		if (ren)
		{ 
			std::cout << "Render created" << std::endl; 
			SDL_SetRenderDrawColor(ren, 255, 255, 255, 255);
		}
		else { exit(1); }

		if (!TTF_Init())
		{
			font = TTF_OpenFont("res/fonts/arial.ttf", 12);
			std::cout << "font loaded" << std::endl;
		}
		else { exit(1); }

		frame_delay = 1000 / fps;
		is_running = true;
		screen = 1;
		wrld.map_tex = load_texture("assets/images/map.png");

		// temporary shit
		sprite_tex[0] = load_texture("assets/images/midrangesheet.png");
	}
}

void Game::loop()
{
	// application window loop
	while (is_running)
	{
		frame_time = SDL_GetTicks64();

		handle_event();
		update();
		render();

		frame_time = SDL_GetTicks64() - frame_time;

		if (frame_time < frame_delay)
		{ SDL_Delay(frame_delay - frame_time); }
	}

	clean();
}

void Game::handle_event()
{
	SDL_PollEvent(&event);
	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (screen == 1)
		{ handle_game_screen1(event.button.x, event.button.y); }
		else if (screen == 2)
		{ handle_game_screen2(event.button.x, event.button.y); }
		else if (screen == 3)
		{ handle_game_screen3(event.button.x, event.button.y); }
		else
		{ handle_start_screen(event.button.x, event.button.y); }
		break;

	case SDL_QUIT:
		is_running = false;
		break;

	default:
		break;
	}
}

void Game::handle_start_screen(int x, int y)
{
	//if (lx < x && x < ux && ly < y && y < uy)
	//{ screen = 1; }
	//if (lx < x && x < ux && ly < y && y < uy)
	//{ screen = 2; }
}

void Game::handle_game_screen1(int x, int y)
{
}

void Game::handle_game_screen2(int x, int y)
{
}

void Game::handle_game_screen3(int x, int y)
{
}

void Game::handle_score_screen()
{
}

void Game::update()
{
	if (wrld.is_playing)
	{
		wrld.update();		// hehe ...prolly not so simple ;-;

	}
	else
	{
		// start, post game screens

	}
	
}

void Game::render()
{
	SDL_RenderClear(ren);
	if (screen && screen < 4)
	{
		SDL_RenderCopy(ren, wrld.map_tex, NULL, NULL);
		for (auto sprite : wrld.sprite_list)
		{ 
			src_rec.x = sprite->src_x;
			src_rec.y = sprite->src_y;
			src_rec.w = sprite->src_w;
			src_rec.h = sprite->src_h;
			des_rec.x = sprite->xscrn;
			des_rec.y = sprite->yscrn;
			des_rec.w = sprite->wscrn;
			des_rec.h = sprite->hscrn;
			SDL_RenderCopy(ren, sprite_tex[sprite->tex_id], &src_rec, &des_rec);
		}
		for (int i = 0; i < 10; i++)
		{
			if (misc_render[i])
			{ SDL_RenderCopy(ren, misc_tex[i], NULL, NULL); }
		}
	}
	
	SDL_RenderPresent(ren);
}

void Game::clean()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}


// set values of misc_render array based on screen and slot value
void Game::set_misc_render()
{
	if (screen)
	{

	}
	else
	{
		misc_render[0] = true;
		for (int i=1; i<9; i++)
		{ misc_render[i] = false; }
	}
}


SDL_Texture* Game::load_texture(const char* img_path)
{
	SDL_Surface* temp_surf = IMG_Load(img_path);
	SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, temp_surf);
	SDL_FreeSurface(temp_surf);
	return tex;
}
