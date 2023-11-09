#include "SDL_image.h"
#include "SDL_mixer.h"
#include "SDL_ttf.h"

#include "cGame.h"

cGame* game = nullptr;

int main(int argc, char* argv[])
{
	game = new cGame();

	game->Initialize("CGP Assessment Project", 960, 540);

	while (game->IsRunning()) 
	{
		game->HandleEvents();
		game->Update();
		game->Draw();
	}

	game->Clean();
	delete game;

	return 0;
}