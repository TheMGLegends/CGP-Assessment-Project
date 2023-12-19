#include <iostream>

#include "cGame.h"
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

	m_textureDictionary[key] = texture;

	return true;
}

// INFO: Used for Drawing Static Textures
void cAssetManager::Draw(std::string key, int x, int y, int width, int height, SDL_RendererFlip flip)
{
	SDL_Rect destinationRect{ x, y, width, height };
	
	if (cGame::Instance()->GetRenderer() != nullptr && m_textureDictionary[key] != nullptr)
	{
		SDL_RenderCopyEx(cGame::Instance()->GetRenderer(), m_textureDictionary[key], NULL, &destinationRect, 0, NULL, flip);
	}
}

// INFO: Used for Drawing Animated Textures
void cAssetManager::Draw(std::string key, int x, int y, int width, int height, int row, int frame, SDL_RendererFlip flip)
{
	SDL_Rect sourceRect = { width * frame, height * row, width, height };
	SDL_Rect destinationRect = { x, y, width, height };

	if (cGame::Instance()->GetRenderer() != nullptr && m_textureDictionary[key] != nullptr)
	{
		SDL_RenderCopyEx(cGame::Instance()->GetRenderer(), m_textureDictionary[key], &sourceRect, &destinationRect, 0, NULL, flip);
	}
}

void cAssetManager::Clean()
{
	for (auto i = m_textureDictionary.begin(); i != m_textureDictionary.end(); i++)
	{
		SDL_DestroyTexture(i->second);
	}

	m_textureDictionary.clear();

	if (m_textureDictionary.empty()) 
	{
		std::cout << "Texture Dictionary is empty!" << std::endl;
	}
	else 
	{
		std::cout << "Texture Dictionary is not empty!" << std::endl;
	}
}
