#include "cGoomba.h"
#include "sGlobalStrings.h"

#include "cEntityManager.h"

#include "MemoryLeakDetector.h"

cEntityManager* cEntityManager::m_Instance = nullptr;

void cEntityManager::LoadEntities(std::vector<std::vector<int>> entityMap)
{
	for (int x = 0; x < entityMap.size(); x++)
	{
		for (int y = 0; y < entityMap[0].size(); y++)
		{
			// INFO: Based on the integer value held in the entity map array a different entity is spawned and added to the entities list so that
			// it can be kept track of
			switch (entityMap[x][y])
			{
			case 1:
				m_entitiesList.push_back(new cGoomba(new sEssentials(static_cast<float>(y * TILE_SIZE), static_cast<float>(x * TILE_SIZE), 16, 16, sGlobalStrings::Goomba_Walk)));
				break;
			default:
				break;
			}
		}
	}
}

void cEntityManager::UpdateEntities(float deltaTime)
{
	for (int i = 0; i < m_entitiesList.size(); i++)
	{
		m_entitiesList[i]->Update(deltaTime);
	}
}

void cEntityManager::DrawEntities()
{
	for (int i = 0; i < m_entitiesList.size(); i++)
	{
		m_entitiesList[i]->Draw();
	}
}

void cEntityManager::Clean()
{
	for (int i = 0; i < m_entitiesList.size(); i++)
	{
		if (m_entitiesList[i] != nullptr) 
		{
			m_entitiesList[i]->Clean();
			delete m_entitiesList[i];
			m_entitiesList[i] = nullptr;
		}
	}

	if (m_Instance != nullptr)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}
