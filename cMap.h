#pragma once

#include "cGame.h"

// INFO TESTING FOR NOW WITH SIMPLE CONSTANT 2D ARRAY
class cMap
{
public:
	void LoadMap(int map[SCREEN_HEIGHT / 32][SCREEN_WIDTH / 32]);
	void DrawMap();
private:
	int m_map[SCREEN_HEIGHT / 32][SCREEN_WIDTH / 32];
	SDL_Rect m_tiles[SCREEN_HEIGHT / 32][SCREEN_WIDTH / 32];
};

