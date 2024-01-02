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
{
}

void cAnimator::Update()
{
	m_animFrame = (SDL_GetTicks() / m_animSpeed) % m_maxFrames;
}

void cAnimator::Draw(int x, int y, int spriteWidth, int spriteHeight) const
{
	cAssetManager::Instance()->DrawAnimation(m_textureKey, x, y, spriteWidth, spriteHeight, m_animRow, m_animFrame, m_animSize, m_flip);
}

void cAnimator::SetAnimation(std::string textureKey, int animRow, int maxFrames, int animSpeed, int animSize, SDL_RendererFlip flip)
{
	m_textureKey = textureKey;
	m_animRow = animRow;
	m_maxFrames = maxFrames;
	m_animSpeed = animSpeed;
	m_animSize = animSize;
	m_flip = flip;
}
