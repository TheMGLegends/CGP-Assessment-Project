#include <SDL.h>

#include "cTime.h"

#include "MemoryLeakDetector.h"

cTime* cTime::m_Instance = nullptr;

void cTime::Update()
{
	m_deltaTime = (float)((SDL_GetTicks() - m_previousFrameTime) / 1000) * TARGET_FPS;

	// INFO: Prevents delta-time from going over the target dt
	if (m_deltaTime > TARGET_DELTATIME) {
		m_deltaTime = TARGET_DELTATIME;
	}

	m_previousFrameTime = (float)SDL_GetTicks();
}

void cTime::Clean()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

cTime::cTime()
	: m_deltaTime{ 0 }
	, m_previousFrameTime{ 0 }
{
	// INFO: Previous ticks are gathered during the construction of time class and the current ticks are called at the end of the game loop found in main
	m_previousFrameTime = (float)SDL_GetTicks();
}
