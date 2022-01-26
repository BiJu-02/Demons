#pragma once

#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

class Game
{
public:
	SDL_Window* _win;
	SDL_Renderer* _ren;
};