#pragma once

#include <string>

#include "SDL.h"

class cAnimator
{
public:
	cAnimator();

	void Update();
	void Draw(int x, int y, int spriteWidth, int spriteHeight);
	void SetAnimation(std::string textureKey, int animRow, int maxFrames, int animSpeed, SDL_RendererFlip flip = SDL_FLIP_NONE);

private:
	int m_animRow;
	int m_animFrame;

	int m_maxFrames;
	int m_animSpeed;

	std::string m_textureKey;
	SDL_RendererFlip m_flip;
};

