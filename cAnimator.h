#pragma once

#include <string>

#include "SDL.h"

class cAnimator
{
public:
	cAnimator();

	void Update();
	void Draw(int x, int y, int spriteWidth, int spriteHeight) const;
	
	// INFO: Used for changing what animation should play
	void SetAnimation(std::string textureKey, int animRow, int maxFrames, int animSpeed, int animSize = 1, SDL_RendererFlip flip = SDL_FLIP_NONE, bool playOneShot = false);

	inline std::string GetCurrentAnimation() const { return m_textureKey; }

private:
	int m_animRow;
	int m_animFrame;
	int m_animSize;

	int m_maxFrames;
	int m_animSpeed;

	std::string m_textureKey;
	SDL_RendererFlip m_flip;

	bool m_bPlayOneShot;
};

