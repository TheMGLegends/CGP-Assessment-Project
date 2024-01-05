#pragma once

#include <SDL.h>

class cInputManager
{
public:
	cInputManager(const cInputManager&) = delete;
	inline static cInputManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cInputManager(); }

	void Update();
	void Clean();

	inline bool GetKey(SDL_Keycode key) { return m_previousKeyboardState[key] && m_keyboardState[key]; }
	inline bool GetKeyDown(SDL_Keycode key) { return !m_previousKeyboardState[key] && m_keyboardState[key]; }
	inline bool GetKeyUp(SDL_Keycode key) { return m_previousKeyboardState[key] && !m_keyboardState[key]; }

private:
	cInputManager();
	static cInputManager* m_Instance;

	Uint8* m_previousKeyboardState;
	const Uint8* m_keyboardState;
	int m_keyLength;
};