#pragma once

#include <vector>

#include "SDL.h"

const int TILE_SIZE = 32;

class cMap
{
public:
	cMap(const cMap&) = delete;
	inline static cMap* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cMap(); }

	void LoadMap(std::vector< std::vector<int> > map);
	void DrawMap();

	inline int GetLevelWidth() const { return m_levelWidth; }
	inline int GetLevelHeight() const { return m_levelHeight; }

	inline int GetColumnCount() const { return m_levelWidth / TILE_SIZE; }
	inline int GetRowCount() const { return m_levelHeight / TILE_SIZE; }

	inline std::vector< std::vector<int> > GetMap() const { return m_map; }

private:
	cMap() : m_levelWidth{ 0 }, m_levelHeight{ 0 } {};
	static cMap* m_Instance;

	int m_levelWidth;
	int m_levelHeight;

	std::vector< std::vector<int> > m_map;
	std::vector< std::vector<SDL_Rect> > m_tiles;
};

