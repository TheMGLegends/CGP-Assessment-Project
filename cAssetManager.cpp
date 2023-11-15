#include "cAssetManager.h"

SDL_Texture* cAssetManager::LoadTexture(const char* filepath, SDL_Renderer* renderer)
{
	SDL_Surface* tempSurface = IMG_Load(filepath);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}
