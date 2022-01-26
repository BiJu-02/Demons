#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#include "Game_Obj.h"

typedef struct
{
	Game_Obj obj;
	SDL_Rect obj_srec, obj_drec;
	SDL_Texture* obj_tex; 
} sprite;

class World
{
public:
	std::vector<sprite> obj_list;
	Game_Obj* hero_arr[6];
	World();
	void obj_create();
	void obj_destroy();
};