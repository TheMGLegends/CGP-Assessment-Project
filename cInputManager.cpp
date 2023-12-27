#include <cstring>
#include <iostream>

#include "cGame.h"

#include "cInputManager.h"

cInputManager* cInputManager::m_Instance = nullptr;

cInputManager::cInputManager()
{
	m_keyboardState = SDL_GetKeyboardState(&m_keyLength);
	m_previousKeyboardState = new Uint8[m_keyLength];
	std::memcpy(m_previousKeyboardState, m_keyboardState, m_keyLength);
}

void cInputManager::Update()
{
	std::memcpy(m_previousKeyboardState, m_keyboardState, m_keyLength);

	SDL_Event sdlEvent{};
	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			cGame::Instance()->SetIsRunning(false);
			break;
		default:
			break;
		}
	}
}

void cInputManager::Clean()
{
	if (m_Instance != nullptr) 
	{
		delete m_Instance;
		m_Instance = nullptr;
	}

	if (m_previousKeyboardState != nullptr)
	{
		delete[] m_previousKeyboardState;
		m_previousKeyboardState = nullptr;
	}
}
