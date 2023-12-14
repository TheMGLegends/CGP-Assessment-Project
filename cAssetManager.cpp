#include <iostream>
#include "SDL_image.h"

#include "cAssetManager.h"

cAssetManager* cAssetManager::m_Instance = nullptr;

bool cAssetManager::LoadTexture(std::string key, const char* filepath, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(filepath);

	if (tempSurface == nullptr) 
	{
		std::cout << "Failed to initialize Surface. SDL error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);

	if (texture == nullptr) 
	{
		std::cout << "Failed to initialize Texture. SDL error: " << SDL_GetError() << std::endl;
		return false;
	}

	SDL_FreeSurface(tempSurface);

	return true;
}
