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
	void Clean();

	inline int GetLevelWidth() const { return m_levelWidth; }
	inline int GetLevelHeight() const { return m_levelHeight; }

	// INFO: 0 is include hence we need to -1
	inline int GetColumnCount() const { return (m_levelWidth / TILE_SIZE) - 1; }
	inline int GetRowCount() const { return (m_levelHeight / TILE_SIZE) - 1; }

	inline std::vector< std::vector<int> > GetMap() const { return m_map; }
	inline std::vector< std::vector<SDL_Rect> > GetTiles() const { return m_tiles; }

private:
	cMap() : m_levelWidth{ 0 }, m_levelHeight{ 0 } {};
	static cMap* m_Instance;

	int m_levelWidth;
	int m_levelHeight;

	// INFO: Texture Data (Based on integer value a different part of the tilemap texture is drawn)
	std::vector< std::vector<int> > m_map;
	
	// INFO: Rect Data (Holds all the x, y, w, h of all the map tiles so that map collision detection can be performed)
	std::vector< std::vector<SDL_Rect> > m_tiles;
};

