#include "cGoomba.h"
#include "cTextureStrings.h"

#include "cEntityManager.h"

#include "MemoryLeakDetector.h"

cEntityManager* cEntityManager::m_Instance = nullptr;

void cEntityManager::LoadEntities(std::vector<std::vector<int>> entityMap)
{
	cCharacter* entity = nullptr;

	for (int x = 0; x < entityMap.size(); x++)
	{
		for (int y = 0; y < entityMap[0].size(); y++)
		{
			switch (entityMap[x][y])
			{
			case 1:
				entity = new cGoomba(new sEssentials(y * TILE_SIZE, x * TILE_SIZE, 16, 16, cTextureStrings::Goomba_Walk));
				m_entitiesList.push_back(entity);
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
