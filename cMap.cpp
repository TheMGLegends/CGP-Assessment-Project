#include <iostream>

#include "cAssetManager.h"
#include "cTextureStrings.h"

#include "cMap.h"

#include "MemoryLeakDetector.h"

cMap* cMap::m_Instance = nullptr;

void cMap::LoadMap(std::vector< std::vector<int> > map)
{
	m_map.resize(map.size());
	m_tiles.resize(map.size());


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

	m_levelWidth = m_map[0].size() * TILE_SIZE;
	m_levelHeight = m_map.size() * TILE_SIZE;
}

void cMap::DrawMap()
{
	for (int x = 0; x < m_map.size(); x++)
	{
		for (int y = 0; y < m_map[0].size(); y++)
		{
			switch (m_map[x][y])
			{
			case 1:
				cAssetManager::Instance()->DrawAnimation(cTextureStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 0, 0);
				break;
			case 2:
				cAssetManager::Instance()->DrawAnimation(cTextureStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 0, 1);
				break;
			case 3:
				cAssetManager::Instance()->DrawAnimation(cTextureStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 1, 0);
				break;
			case 4:
				cAssetManager::Instance()->DrawAnimation(cTextureStrings::Tilemap, m_tiles[x][y].x, m_tiles[x][y].y, m_tiles[x][y].w, m_tiles[x][y].h, 1, 1);
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
