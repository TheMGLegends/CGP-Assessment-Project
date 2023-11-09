#include "cInputManager.h"
#include <cstring>
#include <iostream>

cInputManager* cInputManager::m_Instance = nullptr;

cInputManager::cInputManager()
{
	m_keyboardState = SDL_GetKeyboardState(&m_keyLength);
	m_previousKeyboardState = new Uint8[m_keyLength];
	std::memcpy(m_previousKeyboardState, m_keyboardState, m_keyLength);
}

cInputManager::~cInputManager()
{
	if (m_previousKeyboardState != nullptr) 
	{
		delete[] m_previousKeyboardState;
		m_previousKeyboardState = nullptr;
	}
}

void cInputManager::Update()
{
	std::memcpy(m_previousKeyboardState, m_keyboardState, m_keyLength);
}

void cInputManager::Clean()
{
	if (m_Instance != nullptr) 
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

bool cInputManager::GetKey(SDL_Keycode key)
{
	return m_previousKeyboardState[key] && m_keyboardState[key];
}

bool cInputManager::GetKeyDown(SDL_Keycode key)
{
	return !m_previousKeyboardState[key] && m_keyboardState[key];
}

bool cInputManager::GetKeyUp(SDL_Keycode key)
{
	return m_previousKeyboardState[key] && !m_keyboardState[key];
}