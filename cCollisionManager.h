#pragma once

#include <vector>

#include "SDL.h"

class cCollisionManager
{
public:
	cCollisionManager(const cCollisionManager&) = delete;
	inline static cCollisionManager* Instance() { return m_Instance != nullptr ? m_Instance : m_Instance = new cCollisionManager(); }

	bool ObjectCollision(SDL_Rect objectA, SDL_Rect objectB);
	bool MapCollision(SDL_Rect object);

private:
	cCollisionManager();
	static cCollisionManager* m_Instance;

	std::vector< std::vector<int> > m_levelMap;
};

