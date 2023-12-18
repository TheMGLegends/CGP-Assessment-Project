#pragma once

#include <string>
#include "cTransform.h"
#include "SDL.h"

struct sParameters
{
	sParameters(float x, float y, int width, int height, std::string textureKey, SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		X = x;
		Y = y;
		Width = width;
		Height = height;
		Flip = flip;
		TextureKey = textureKey;
	}

	float X;
	float Y;
	int Width;
	int Height;
	SDL_RendererFlip Flip;
	std::string TextureKey;
};

class cGameObject
{
public:
	cGameObject(sParameters* params);

	// INFO: Required GO Methods:
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;

protected:
	cTransform* m_position;
	int m_width;
	int m_height;
	SDL_RendererFlip m_flip;
	std::string m_textureKey;
	
};