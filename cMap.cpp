#include <iostream>

#include "cAssetManager.h"
#include "sGlobalStrings.h"

#include "cMap.h"

#include "MemoryLeakDetector.h"

cMap* cMap::m_Instance = nullptr;

void cMap::LoadMap(std::vector< std::vector<int> > map)
{
	// INFO: Resizes the 2D vector arrays that hold the map data as well as the tile data to match the size of the passed in map
	m_map.resize(map.size());
	m_tiles.resize(map.size());

	// INFO: Loops through all the elements held inside of the map and assigns their values to the local m_map variable
	// It also assigns the necessary values to the tiles' array to ensure that each tile is drawn correctly (X, Y, Width and Height)
	for (int x = 0; x < map.size(); x++)
	{
		m_map[x].resize(map[x].size());
		m_tiles[x].resize(map[x].size());

		for (int y = 0; y < map[0].size(); y++)
		{
			m_map[x][y] = map[x][y];

			m_tiles[x][y].x = y * TILE_SIZE;
			m_tiles[x][y].y = x * TILE_SIZE;
			m_tiles[x][y].w = TILE_SIZE;
			m_tiles[x][y].h = TILE_SIZE;
		}
	}

	m_levelWidth = static_cast<int>(m_map[0].size() * TILE_SIZE);
	m_levelHeight = static_cast<int>(m_map.size() * TILE_SIZE);
}

void cMap::DrawMap()
{
	for (int x = 0; x < m_map.size(); x++)
	{
		for (int y = 0; y < m_map[0].size(); y++)
		{
			// INFO: Based on the integer value held at a specific position inside of the m_map variable a different part of a specified texture is drawn
			// in this case it uses the Tilemap texture
			switch (m_map[x][y])
			{
			case 1:
				cAssetManager::Instance()->DrawAnimation(sGlobalStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 0, 0);
				break;
			case 2:
				cAssetManager::Instance()->DrawAnimation(sGlobalStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 0, 1);
				break;
			case 3:
				cAssetManager::Instance()->DrawAnimation(sGlobalStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 1, 0);
				break;
			case 4:
				cAssetManager::Instance()->DrawAnimation(sGlobalStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 1, 1);
				break;
			default:
				break;
			}
		}
	}
}

void cMap::Clean()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}
