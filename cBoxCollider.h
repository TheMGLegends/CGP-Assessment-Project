#pragma once

#include "SDL.h"

class cBoxCollider
{
public:
	inline SDL_Rect GetBoxCollider() const { return m_boxCollider; }

	void Update(int x, int y, int w, int h);

	void DrawBoxCollider();

private:
	SDL_Rect m_boxCollider;
};

