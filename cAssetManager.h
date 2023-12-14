#pragma once
#include <string>
#include <SDL.h>

class cAssetManager
{
public:
	cAssetManager(const cAssetManager&) = delete;
	inline static cAssetManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cAssetManager(); }

	bool LoadTexture(std::string key, const char* filepath, SDL_Renderer* renderer);

private:
	cAssetManager() {};
	static cAssetManager* m_Instance;

};