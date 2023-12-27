#include "cGame.h"

int main(int argc, char* argv[])
{
	cGame::Instance()->Initialise("CGP Assessment Project");

	while (cGame::Instance()->GetIsRunning())
	{
		cGame::Instance()->HandleEvents();
		cGame::Instance()->Update(0);
		cGame::Instance()->Draw();
	}

	cGame::Instance()->Clean();

	return 0;
}