#pragma once
#include "cVector2.h"
#include "SDL.h"

class cGameObject
{
public:
	virtual void Update() = 0;
	void Draw(SDL_Renderer* renderer);

protected:
	cVector2 m_position;
	int m_width;
	int m_height;
	bool m_isActive;
	SDL_Texture* m_texture;
	SDL_Rect m_srcRect;

private:
};