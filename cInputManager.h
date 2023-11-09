#pragma once
#include <SDL.h>

class cInputManager
{
public:
	cInputManager(const cInputManager&) = delete;
	inline static cInputManager* GetInstance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cInputManager(); }

	void Update();
	void Clean();

	bool GetKey(SDL_Keycode key);
	bool GetKeyDown(SDL_Keycode key);
	bool GetKeyUp(SDL_Keycode key);

protected:

private:
	cInputManager();
	~cInputManager();

	static cInputManager* m_Instance;

	Uint8* m_previousKeyboardState;
	const Uint8* m_keyboardState;
	int m_keyLength;
};