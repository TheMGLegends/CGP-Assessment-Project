#pragma once

#include <vector>

const int TILE_WIDTH = 32;
const int TILE_HEIGHT = 32;

class cMap
{
public:
	cMap(const cMap&) = delete;
	inline static cMap* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cMap(); }

	void LoadMap(std::vector< std::vector<int> > map);
	void DrawMap();

	inline int GetLevelWidth() const { return m_levelWidth; }
private:
	cMap() : m_levelWidth{ 0 } {};
	static cMap* m_Instance;

	int m_levelWidth;

	std::vector< std::vector<int> > m_map;
	std::vector< std::vector<SDL_Rect> > m_tiles;
};

