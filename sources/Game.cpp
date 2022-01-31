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
		// for actual game screen = 0;
		screen = 0; 
		set_misc_render();
		wrld.map_tex = load_texture("assets/images/map.png");
		icons = load_texture("assets/images/icons.png");

		// load all misc_tex


		// temporary shit
		misc_tex[0] = load_texture("assets/images/blank.png");
		misc_tex[1] = load_texture("assets/images/hud.png");
		sprite_tex[0] = load_texture("assets/images/minionenemyspritesheet.png");
		sprite_tex[1] = load_texture("assets/images/midenemyspritesheet.png");
		sprite_tex[2] = load_texture("assets/images/bossenemyspritesheet.png");
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
		{ handle_game_screen(event.button.x, event.button.y); }
		
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
	// for start butt
	if (10 < x && x < 1250 && 10 < y && y < 700)
	{
		screen = 1; 
		wrld.start_game(); 
		set_misc_render();
	}
	// for credits butt
	//if (lx < x && x < ux && ly < y && y < uy)
	//{ screen = 2; }
}

void Game::handle_game_screen(int x, int y)
{
	// if quit button is pressed ...is_paused = true ...and dialog box for confirmation
	// if quit confirmed ...wrld.exit_game() ...screen = 0
	if (1170 < x && x < 1230 && 10 < y && y < 70)		// pause / play
	{
		if (!wrld.is_playing)
		{ wrld.is_playing = true; std::cout << "playing" << std::endl; }
		else if (wrld.is_paused)
		{ wrld.is_paused = false; std::cout << "resumed" << std::endl; }
		else
		{ wrld.is_paused = true; std::cout << "paused" << std::endl; }
	}
	//hero slot
	else if (!wrld.is_paused)
	{
		if (640 < y)
		{
			if (760 < x && x < 1240)			// hero slots
			{
				int tmpx = 840;
				for (int i = 0; i < 6; i++)
				{
					if (x < tmpx)
					{
						wrld.slot = i;
						std::cout << wrld.slot << std::endl;
						set_misc_render();
						break;
					}
					else
					{ tmpx += 80; }
				}
			}
			else if (540 < x && x < 560)
			{
				if (wrld.slot != -1)
				{
					if (wrld.hero_arr[wrld.slot])
					{
						// upgrade

					}
					else
					{
						// hero selection
						
					}
				}
			}
			else
			{ wrld.slot = -1; }
		}
		else if (120 < y)		//map
		{
			if (wrld.slot != -1)
			{
				if (wrld.hero_arr[wrld.score])
				{
					wrld.hero_arr[wrld.slot]->set_camp(x, y);
				}
				else
				{ wrld.slot = -1; }
			}
		}
		else
		{ wrld.slot = -1; }
	}

}


void Game::handle_score_screen()
{

}


void Game::update()
{
	if (screen == 1)
	{
		if (!wrld.is_paused)
		{ wrld.update(); }
		if (wrld.lives < 1)
		{
			screen = 3;
			wrld.exit_game();
		}
	}
	if (screen == 3)
	{
		
	}
}

void Game::render()
{
	SDL_RenderClear(ren);
	if (screen == 1)
	{ render_game_screen(); }
	else
	{ SDL_RenderCopy(ren, misc_tex[0], NULL, NULL); }
	
	SDL_RenderPresent(ren);
}

inline void Game::render_game_screen()
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
		{
			SDL_RenderCopy(ren, misc_tex[i], NULL, NULL);
		}
	}
	// icons...hoe to do dis?
	if (!wrld.is_playing || wrld.is_paused)
	{ src_rec.x = 120; src_rec.y = 0; }
	else
	{ src_rec.x = 80; src_rec.y = 0; }
	src_rec.w = 40; src_rec.h = 40;
	des_rec.x = 1170; des_rec.y = 10;
	des_rec.w = 60; des_rec.h = 60;
	SDL_RenderCopy(ren, icons, &src_rec, &des_rec);

	if (wrld.slot != -1)
	{
		if (wrld.hero_arr[wrld.slot])
		{
			// render update button
			// display stats...icons and text
		}
		else
		{
			// render hero options to spawn...
		}
	}

	// ze texts on hud at top

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
	if (screen == 1)
	{
		misc_render[0] = false;
		misc_render[1] = true;

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
