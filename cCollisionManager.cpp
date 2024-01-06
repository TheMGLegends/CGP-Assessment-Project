#include "cCamera.h"
#include "cGame.h"
#include "cMap.h"

#include "cCollisionManager.h"

#include "MemoryLeakDetector.h"

cCollisionManager* cCollisionManager::m_Instance = nullptr;

void cCollisionManager::Clean()
{
	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}

// INFO: AABB Collision Detection
bool cCollisionManager::ObjectCollision(SDL_Rect objectA, SDL_Rect objectB)
{
	if (objectA.x + objectA.w >= objectB.x && objectA.x <= objectB.x + objectB.w &&
		objectA.y + objectA.h >= objectB.y && objectA.y <= objectB.y + objectB.h)
		return true;
	return false;
}

// INFO: Used to check collisions between a GO and the map, instead of having to check through all map tiles every frame
// this way only the left, right, top and bottom tiles found around the GO need to be checked through to ensure the GO
// isn't going through any of them
bool cCollisionManager::MapCollision(SDL_Rect object)
{
	int columnCount = cMap::Instance()->GetColumnCount();
	int rowCount = cMap::Instance()->GetRowCount();

	// INFO: Dividing by tile size is done as some GOs may not conform to the tile size and may be bigger than this
	int leftTile = object.x / TILE_SIZE;
	int rightTile = (object.x + object.w) / TILE_SIZE;

	int topTile = object.y / TILE_SIZE;
	int bottomTile = (object.y + object.h) / TILE_SIZE;

	// INFO: Ensures if the GO is standing on an edge that it doesn't access tiles that do not actually exist
	if (leftTile < 0) leftTile = 0;
	if (rightTile > columnCount) rightTile = columnCount;
	
	if (topTile < 0) topTile = 0;
	if (bottomTile > rowCount) bottomTile = rowCount;

	for (int i = leftTile; i <= rightTile; i++) 
	{
		for (int j = topTile; j <= bottomTile; j++) 
		{
			// INFO: If any of the integer values held inside of the map array are greater than 0 (Meaning there is a block there) 
			// a collision must have occured, therefore needs to be taken into account (Prevent GO from going there)
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
