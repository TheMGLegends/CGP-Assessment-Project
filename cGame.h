#pragma once

#include <SDL.h>

const int SCREEN_WIDTH = 960;
const int SCREEN_HEIGHT = 480;

const float LEVEL_COMPLETE_INTERVAL = 360.0f;

const int TIME_BONUS = 5000;

class cGame
{
public:
	cGame(const cGame&) = delete;
	inline static cGame* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cGame(); }

	bool Initialise(const char* windowTitle, int width = SCREEN_WIDTH, int height = SCREEN_HEIGHT);
	void HandleEvents();
	void Update(float deltaTime);
	void Draw();
	void Clean();
	void ResetGame();

	inline SDL_Renderer* GetRenderer() const { return m_renderer; }
	inline bool GetIsRunning() const { return m_bIsRunning; }

	inline void SetIsRunning(bool isRunning) { m_bIsRunning = isRunning; }
	inline void SetLevelCompleted(bool isLevelCompleted) { m_bLevelCompleted = isLevelCompleted; }

private:
	cGame();
	static cGame* m_Instance;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;
	bool m_bIsRunning;

	bool m_bLevelCompleted;
	float m_levelCompleteTime;

	int m_bonusScore;

	float m_currentTime;
	float m_resetTime;
};