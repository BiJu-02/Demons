#include "Game.h"


Game::Game(const char* title, int x, int y, int w, int h, int sc, int fps)
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
	}
}

void Game::loop()
{
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
	case SDL_QUIT:
		is_running = false;
		break;
	default:
		break;
	}
}

void Game::update()
{

}

void Game::render()
{
	SDL_RenderClear(ren);

	SDL_RenderPresent(ren);
}

void Game::clean()
{
	SDL_DestroyWindow(win);
	SDL_DestroyRenderer(ren);
	SDL_Quit();
	std::cout << "game cleaned" << std::endl;
}

