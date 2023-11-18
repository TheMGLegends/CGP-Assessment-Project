#pragma once
#include <SDL.h>
#include "cInputManager.h"

class cGame
{
public:
	cGame();
	~cGame();

	/*
	* @param xPosition: By default is SDL_WINDOWPOS_CENTERED
	* @param yPosition: By default is SDL_WINDOWPOS_CENTERED
	*/
	bool Initialize(const char* windowTitle, int width, int height, int xPosition = SDL_WINDOWPOS_CENTERED, int yPosition = SDL_WINDOWPOS_CENTERED);
	void HandleEvents();
	void Update();
	void Draw();
	void Clean();

	bool IsRunning();

protected:

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	cInputManager* m_inputManager;
	bool m_isRunning;

	// INFO: Temporary Testing:
	int count = 0;
};