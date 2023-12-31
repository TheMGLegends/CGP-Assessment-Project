#pragma once

#include "SDL.h"

class cBoxCollider
{
public:
	inline SDL_Rect GetBoxCollider() const { return m_boxCollider; }

private:
	SDL_Rect m_boxCollider;
};

