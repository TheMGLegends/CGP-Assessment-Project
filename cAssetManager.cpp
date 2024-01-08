#include <iostream>

#include "cCamera.h"
#include "cGame.h"
#include "cVector2.h"
#include "SDL_image.h"

#include "cAssetManager.h"

#include "MemoryLeakDetector.h"

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

// INFO: Used for Drawing things like UI elements
void cAssetManager::DrawUI(SDL_Texture* texture, int x, int y, int width, int height, int size, SDL_RendererFlip flip)
{
	SDL_Rect destinationRect = { x, y, width * size, height * size };

	if (cGame::Instance()->GetRenderer() != nullptr && texture != nullptr)
	{
		SDL_RenderCopyEx(cGame::Instance()->GetRenderer(), texture, NULL, &destinationRect, 0, NULL, flip);
	}
}

// INFO: Used for Drawing things like drawing entity states that do not have an animation
void cAssetManager::Draw(std::string key, int x, int y, int width, int height, float scrollingSpeed, int size, SDL_RendererFlip flip)
{
	cVector2 cameraPos = cCamera::Instance()->GetPosition() * scrollingSpeed;
	SDL_Rect destinationRect = { static_cast<int>(x - cameraPos.m_x), static_cast<int>(y - cameraPos.m_y), width * size, height * size };
	
	if (cGame::Instance()->GetRenderer() != nullptr && m_textureDictionary[key] != nullptr)
	{
		SDL_RenderCopyEx(cGame::Instance()->GetRenderer(), m_textureDictionary[key], NULL, &destinationRect, 0, NULL, flip);
	}
}

// INFO: Used for Drawing Animated Objects + Sections of Textures like Tilemap Pieces
void cAssetManager::DrawAnimation(std::string key, int x, int y, int width, int height, int row, int frame, int size, SDL_RendererFlip flip)
{
	SDL_Rect sourceRect = { width * frame, height * row, width, height };
	cVector2 cameraPos = cCamera::Instance()->GetPosition();
	SDL_Rect destinationRect = { static_cast<int>(x - cameraPos.m_x), static_cast<int>(y - cameraPos.m_y), width * size, height * size };

	if (cGame::Instance()->GetRenderer() != nullptr && m_textureDictionary[key] != nullptr)
	{
		SDL_RenderCopyEx(cGame::Instance()->GetRenderer(), m_textureDictionary[key], &sourceRect, &destinationRect, 0, NULL, flip);
	}
}

bool cAssetManager::LoadFont(std::string key, const char* filepath, int fontSize)
{
	TTF_Font* font = TTF_OpenFont(filepath, fontSize);

	if (font == nullptr)
	{
		std::cout << "Failed to initialize Font. SDL_TTF error: " << TTF_GetError() << std::endl;
		return false;
	}

	m_fontDictionary[key] = font;

	return true;
}

void cAssetManager::Clean()
{
	for (auto i = m_textureDictionary.begin(); i != m_textureDictionary.end(); i++)
	{
		SDL_DestroyTexture(i->second);
	}

	m_textureDictionary.clear();

	if (m_textureDictionary.empty()) 
		std::cout << "Texture Dictionary is empty!" << std::endl;
	else 
		std::cout << "Texture Dictionary is not empty!" << std::endl;

	for (auto i = m_fontDictionary.begin(); i != m_fontDictionary.end(); i++)
	{
		TTF_CloseFont(i->second);
	}

	m_fontDictionary.clear();

	if (m_fontDictionary.empty())
		std::cout << "Font Dictionary is empty!" << std::endl;
	else
		std::cout << "Font Dictionary is not empty!" << std::endl;

	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}
