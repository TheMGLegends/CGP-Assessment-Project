#include <iostream>

#include "cGame.h"
#include "sGlobalStrings.h"

#include "cUILabel.h"

#include "MemoryLeakDetector.h"

cUILabel::cUILabel(float x, float y, int scale, std::string text)
	: m_pendingLabelText{ "" }
	, m_currentLabelText{ "" }
	, m_width{ 10 }
	, m_height{ 10 }
{
	m_position = new cTransform(x, y);
	m_scale = scale;

	// INFO: White by Default
	m_textColor = { 255, 255, 255, 255 };
	m_labelTexture = nullptr;

	ChangeText(text);
}

bool cUILabel::ChangeText(std::string labelText)
{
	m_pendingLabelText = labelText;

	if (m_pendingLabelText != m_currentLabelText) 
	{
		SDL_Surface* textSurface = TTF_RenderText_Blended(cAssetManager::Instance()->GetFont(sGlobalStrings::PixelArt_Font), m_pendingLabelText.c_str(), m_textColor);
		m_labelTexture = SDL_CreateTextureFromSurface(cGame::Instance()->GetRenderer(), textSurface);

		if (m_labelTexture == nullptr)
		{
			std::cout << "Texture was not created successfully. SDL error: " << SDL_GetError() << std::endl;
			return false;
		}

		SDL_FreeSurface(textSurface);

		// INFO: Ensures that the width and height when drawn is precisely what it was when the texture was created
		// this should prevent stretching and distortion
		SDL_QueryTexture(m_labelTexture, nullptr, nullptr, &m_width, &m_height);

		std::cout << "Label Text Changed!" << std::endl;

		m_currentLabelText = m_pendingLabelText;

		return true;
	}
	
	std::cout << "Label Text not changed as texts are the same!" << std::endl;
	return false;
}

void cUILabel::Draw()
{
	cAssetManager::Instance()->DrawUI(m_labelTexture, static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), m_width, m_height, m_scale);
}

void cUILabel::Clean()
{
	if (m_position != nullptr)
	{
		delete m_position;
		m_position = nullptr;
	}

	if (m_labelTexture != nullptr)
	{
		SDL_DestroyTexture(m_labelTexture);
		m_labelTexture = nullptr;
	}
}
