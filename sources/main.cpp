#include "Game.h"

int main(int argc, char* argv[])
{
	Game g("oops", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0, 60);
	g.loop();
	return 0;
}