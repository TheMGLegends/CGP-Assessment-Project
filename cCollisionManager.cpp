#include "cCamera.h"
#include "cGame.h"
#include "cMap.h"

#include "cCollisionManager.h"

cCollisionManager* cCollisionManager::m_Instance = nullptr;

bool cCollisionManager::ObjectCollision(SDL_Rect objectA, SDL_Rect objectB)
{
	if (objectA.x + objectA.w > objectB.x && objectA.x < objectB.x + objectB.w &&
		objectA.y + objectA.h > objectB.y && objectA.y < objectB.y + objectB.h)
		return true;
	return false;
}

bool cCollisionManager::MapCollision(SDL_Rect object)
{
	int columnCount = cMap::Instance()->GetColumnCount();
	int rowCount = cMap::Instance()->GetRowCount();

	int leftTile = object.x / TILE_SIZE;
	int rightTile = (object.x + object.w) / TILE_SIZE;

	int topTile = object.y / TILE_SIZE;
	int bottomTile = (object.y + object.h) / TILE_SIZE;

	if (leftTile < 0) leftTile = 0;
	if (rightTile > columnCount) rightTile = columnCount;
	
	if (topTile < 0) topTile = 0;
	if (bottomTile > rowCount) bottomTile = rowCount;

	for (int i = leftTile; i <= rightTile; i++) 
	{
		for (int j = topTile; j <= bottomTile; j++) 
		{
			if (m_levelMap[j][i] > 0)
				return true;
		}
	}
	return false;
}

cCollisionManager::cCollisionManager()
{
	m_levelMap = cMap::Instance()->GetMap();
	m_rectMap = cMap::Instance()->GetTiles();
}
