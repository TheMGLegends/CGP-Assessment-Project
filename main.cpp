#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include <iostream>

#include "cTime.h"
#include "cGame.h"

cGame* game = nullptr;

int main(int argc, char* argv[])
{
	game = new cGame();

	game->Initialize("CGP Assessment Project", 960, 540);

	Uint32 previousFrameTicks = SDL_GetTicks();

	while (game->IsRunning()) 
	{
		cTime::m_deltaTime = (SDL_GetTicks() - (float)(previousFrameTicks)) / 1000;
		previousFrameTicks = SDL_GetTicks();

		game->HandleEvents();
		game->Update();
		game->Draw();

	}

	game->Clean();
	delete game;

	return 0;
}