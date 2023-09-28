#include <iostream>
#include "SDL.h"

int main(int argc, char* argv[])
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "Failed to initialize SDL. SDL error: " << SDL_GetError() << std::endl;
	}

	SDL_Quit();

	return 0;
}