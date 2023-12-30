#include "cMap.h"

#include "cAssetManager.h"
#include "cTextureStrings.h"

void cMap::LoadMap(int map[SCREEN_HEIGHT / 32][SCREEN_WIDTH / 32])
{
	for (int row = 0; row < SCREEN_HEIGHT / 32; row++)
	{
		for (int column = 0; column < SCREEN_WIDTH / 32; column++)
		{
			m_map[row][column] = map[row][column];
			m_tiles[row][column] = { row * 32, column * 32, 32, 32 };
		}
	}
}

void cMap::DrawMap()
{
	for (int row = 0; row < SCREEN_HEIGHT / 32; row++)
	{
		for (int column = 0; column < SCREEN_WIDTH / 32; column++)
		{
			switch (m_map[row][column])
			{
			case 1:
				cAssetManager::Instance()->DrawFrame(cTextureStrings::Tilemap, m_tiles[row][column].x, m_tiles[row][column].y, 0, 0);
				break;
			case 2:
				cAssetManager::Instance()->DrawFrame(cTextureStrings::Tilemap, m_tiles[row][column].x, m_tiles[row][column].y, 0, 1);
				break;
			case 3:
				cAssetManager::Instance()->DrawFrame(cTextureStrings::Tilemap, m_tiles[row][column].x, m_tiles[row][column].y, 1, 0);
				break;
			case 4:
				cAssetManager::Instance()->DrawFrame(cTextureStrings::Tilemap, m_tiles[row][column].x, m_tiles[row][column].y, 1, 1);
				break;
			default:
				break;
			}
		}
	}
}
