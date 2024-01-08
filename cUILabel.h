#pragma once

#include <string>

#include "cAssetManager.h"
#include "cTransform.h"

#include "SDL.h"
#include "SDL_ttf.h"

class cUILabel
{
public:
	cUILabel(float x, float y, int scale = 1, std::string text = "New Text");

	bool ChangeText(std::string labelText);
	void ChangeLabelPos(float x, float y);

	void Draw() const;
	void Clean();

	inline int GetWidth() const { return m_width; }
	inline int GetHeight() const { return m_height; }

private:
	cTransform* m_position;
	SDL_Color m_textColor;
	SDL_Texture* m_labelTexture;

	int m_width;
	int m_height;
	int m_scale;

	std::string m_currentLabelText;
	std::string m_pendingLabelText;
};

