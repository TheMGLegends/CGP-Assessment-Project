#include <stdlib.h>
#include <time.h>

#include "cGame.h"
#include "cTime.h"

#include "MemoryLeakDetector.h"

int main(int argc, char* argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	srand(unsigned int(time(NULL)));
	cGame::Instance()->Initialise("CGP Assessment Project");

	while (cGame::Instance()->GetIsRunning())
	{
		cGame::Instance()->HandleEvents();
		cGame::Instance()->Update(cTime::Instance()->DeltaTime());
		cGame::Instance()->Draw();	
		cTime::Instance()->Update();
	}

	cTime::Instance()->Clean();
	cGame::Instance()->Clean();

	return 0;
}