#pragma once
#include <SDL.h>
#include <SDL_image.h>

class cAssetManager
{
public:
	static SDL_Texture* LoadTexture(const char* filepath, SDL_Renderer* renderer);
protected:

private:
};