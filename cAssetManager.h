#pragma once

#include <unordered_map>
#include <string>
#include <SDL.h>

class cAssetManager
{
public:
	cAssetManager(const cAssetManager&) = delete;
	inline static cAssetManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cAssetManager(); }

	bool LoadTexture(std::string key, const char* filepath, SDL_Renderer* renderer);

	void DrawStatic(std::string key, int x, int y, int width, int height, int size = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);
	void DrawFrame(std::string key, int x, int y, int width, int height, int row = 0, int frame = 0, int size = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

	void Clean();

private:
	cAssetManager() {};
	static cAssetManager* m_Instance;

	std::unordered_map<std::string, SDL_Texture*> m_textureDictionary;
};