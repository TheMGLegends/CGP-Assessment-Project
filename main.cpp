//#include "SDL_image.h"
//#include "SDL_mixer.h"
//#include "SDL_ttf.h"

#include <iostream>
//#include "cTime.h"

#include "cGame.h"

int main(int argc, char* argv[])
{
	cGame::Instance()->Initialise("CGP Assessment Project", 960, 540);

	//Uint32 previousFrameTicks = SDL_GetTicks();

	while (cGame::Instance()->IsRunning())
	{
		//cTime::m_deltaTime = (SDL_GetTicks() - (float)(previousFrameTicks)) / 1000;
		//previousFrameTicks = SDL_GetTicks();

		cGame::Instance()->HandleEvents();
		cGame::Instance()->Update();
		cGame::Instance()->Draw();

	}

	cGame::Instance()->Clean();

	return 0;
}