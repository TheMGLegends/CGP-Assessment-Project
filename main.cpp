#include <iostream>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "cGame.h"

int main(int argc, char* argv[])
{
	cGame game;

	game.Initialize("CGP Assessment Project", 960, 540);

	while (game.IsRunning()) 
	{
		game.HandleEvents();
		game.Update();
		game.Draw();
	}

	game.Clean();

	return 0;
}