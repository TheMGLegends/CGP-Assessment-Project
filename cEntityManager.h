#pragma once

#include <vector>

#include "cCharacter.h"
#include "cMap.h"
#include "cPickups.h"

class cEntityManager
{
public:
	cEntityManager(const cEntityManager&) = delete;
	inline static cEntityManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cEntityManager(); }

	void LoadEntities(std::vector< std::vector<int> > entityMap);
	void UpdateEntities(float deltaTime);
	void DrawEntities();
	void Clean();

	std::vector<cCharacter*> GetEntities() const { return m_entitiesList; }
	std::vector<cPickups*> GetPickups() const { return m_pickupsList; }

private:
	cEntityManager() {};
	static cEntityManager* m_Instance;

	std::vector<cCharacter*> m_entitiesList;
	std::vector<cPickups*> m_pickupsList;
};

