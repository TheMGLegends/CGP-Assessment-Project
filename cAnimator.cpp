#include <iostream>

#include "cAnimator.h"

#include "cAssetManager.h"

cAnimator::cAnimator() 
	: m_animRow{ 0 }
	, m_animFrame{ 0 }
	, m_animSize{ 1 }
	, m_maxFrames{ 0 }
	, m_animSpeed{ 0 }
	, m_textureKey{ "" }
	, m_flip{ SDL_FLIP_NONE }
	, m_bPlayOneShot{ false }
	, m_bAnimationCompleted{ false }
	, m_bSetAnimation{ false }
{
}

void cAnimator::Update()
{
	m_animFrame = (SDL_GetTicks() / m_animSpeed) % m_maxFrames;

	// INFO: Prevents Skipping of Animation
	if (m_bSetAnimation && m_bPlayOneShot)
	{
		m_animFrame = 0;
		m_bSetAnimation = false;
	}

	// INFO: Ensures Animation is only ever played through once
	if (m_bPlayOneShot && m_animFrame == m_maxFrames - 1) 
	{
		m_animFrame = m_maxFrames - 1;
		m_bAnimationCompleted = true;
	}



	std::cout << "ANIM FRAME: " << m_animFrame << std::endl;
	std::cout << "MAX FRAMES: " << m_maxFrames << std::endl;
}

void cAnimator::Draw(int x, int y, int spriteWidth, int spriteHeight) const
{
	cAssetManager::Instance()->DrawAnimation(m_textureKey, x, y, spriteWidth, spriteHeight, m_animRow, m_animFrame, m_animSize, m_flip);
}

void cAnimator::SetAnimation(std::string textureKey, int animRow, int maxFrames, int animSpeed, int animSize, SDL_RendererFlip flip, bool playOneShot)
{
	m_bAnimationCompleted = false;
	m_bSetAnimation = true;

	m_textureKey = textureKey;
	m_animRow = animRow;
	m_maxFrames = maxFrames;
	m_animSpeed = animSpeed;
	m_animSize = animSize;
	m_flip = flip;
	m_bPlayOneShot = playOneShot;
}

bool cAnimator::GetAnimationCompleted(std::string currentAnimation) const
{
	if (m_textureKey == currentAnimation && m_bAnimationCompleted)
		return true;
	return false;
}
