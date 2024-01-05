#include <SDL.h>

#include "cTime.h"

#include "MemoryLeakDetector.h"

cTime* cTime::m_Instance = nullptr;

void cTime::Update()
{
	m_deltaTime = (float)((SDL_GetTicks() - m_previousFrameTime) / 1000) * TARGET_FPS;

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
	m_previousFrameTime = (float)SDL_GetTicks();
}
