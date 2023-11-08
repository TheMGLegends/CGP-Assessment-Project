#pragma once
#include <SDL.h>

class cGame
{
public:
	cGame();
	~cGame();

	/*
	* @param xPosition: By default is SDL_WINDOWPOS_CENTERED
	* @param yPosition: By default is SDL_WINDOWPOS_CENTERED
	*/
	void Initialize(const char* windowTitle, int width, int height, int xPosition = SDL_WINDOWPOS_CENTERED, int yPosition = SDL_WINDOWPOS_CENTERED);
	void HandleEvents();
	void Update();
	void Draw();
	void Clean();

	bool IsRunning();

protected:

private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	const Uint8* m_keyboardState;
	bool m_isRunning;
};