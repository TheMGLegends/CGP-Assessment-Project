#pragma once

#include "SDL.h"

class cBoxCollider
{
public:
	inline SDL_Rect GetRect() const { return m_rectCollider; }

	void UpdateCollider(int x, int y, int w, int h);
	void DrawBoxCollider();

private:
	SDL_Rect m_rectCollider;
};

