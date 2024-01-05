#pragma once

#include <string>

#include "cTransform.h"

#include "SDL.h"

// INFO: Essential Variables that must be initialized are kept inside of a struct so that each class that inherits from cGameObject
// doesn't need a long constructor full of parameters (easier to write)
struct sEssentials
{
	sEssentials(float x, float y, int width, int height, std::string textureKey = "", SDL_RendererFlip flip = SDL_FLIP_NONE)
	{
		_x = x;
		_y = y;
		_width = width;
		_height = height;
		_textureKey = textureKey;
		_flip = flip;
	}

	float _x;
	float _y;
	int _width;
	int _height;
	std::string _textureKey;
	SDL_RendererFlip _flip;
};

class cGameObject
{
public:
	cGameObject(sEssentials* required);

	// INFO: Required GO Methods
	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;

	virtual void Clean();

	inline cTransform* GetCenterPoint() { return m_centerPoint; }

protected:
	// INFO: Point used by cCamera to follow the center of the object
	cTransform* m_centerPoint;

	cTransform* m_position;
	int m_width;
	int m_height;
	std::string m_textureKey;
	SDL_RendererFlip m_flip;
};