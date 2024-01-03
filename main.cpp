#include <stdlib.h>
#include <time.h>

#include "cGame.h"
#include "cTime.h"

int main(int argc, char* argv[])
{
	srand(unsigned int(time(NULL)));
	cGame::Instance()->Initialise("CGP Assessment Project");

	while (cGame::Instance()->GetIsRunning())
	{
		cGame::Instance()->HandleEvents();
		cGame::Instance()->Update(cTime::Instance()->DeltaTime());
		cGame::Instance()->Draw();	
		cTime::Instance()->Update();
	}

	cGame::Instance()->Clean();

	return 0;
}