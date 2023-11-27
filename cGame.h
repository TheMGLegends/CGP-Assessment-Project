#pragma once
#include <SDL.h>
//#include "cInputManager.h"

class cGame
{
public:
	cGame(const cGame&) = delete;
	inline static cGame* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cGame(); }

	bool Initialise(const char* windowTitle, int width, int height);
	void HandleEvents();
	void Update();
	void Draw();
	void Clean();

	inline bool IsRunning() const { return m_isRunning; }
	inline SDL_Renderer* GetRenderer() const { return m_renderer; }

private:
	cGame();

	static cGame* m_Instance;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_isRunning;
	//cInputManager* m_inputManager;

	// INFO: Temporary Testing:
	//int count = 0;
};