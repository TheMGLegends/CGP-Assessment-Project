#pragma once

#include <unordered_map>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

class cAssetManager
{
public:
	cAssetManager(const cAssetManager&) = delete;
	inline static cAssetManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cAssetManager(); }

	bool LoadTexture(std::string key, const char* filepath, SDL_Renderer* renderer);

	// INFO: Used to draw the map
	void Draw(std::string key, int x, int y, int width, int height, float scrollingSpeed = 1.0f, int size = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);

	// INFO: Used to draw animated textures
	void DrawAnimation(std::string key, int x, int y, int width, int height, int row = 0, int frame = 0, int size = 1, SDL_RendererFlip flip = SDL_FLIP_NONE);


	bool LoadFont(std::string key, const char* filepath, int fontSize);

	// INFO: Used to Retrieve a Font
	inline TTF_Font* GetFont(std::string key) { if (m_fontDictionary[key] != nullptr) return m_fontDictionary[key]; }

	void Clean();

private:
	cAssetManager() {};
	static cAssetManager* m_Instance;

	std::unordered_map<std::string, SDL_Texture*> m_textureDictionary;
	std::unordered_map<std::string, TTF_Font*> m_fontDictionary;
};