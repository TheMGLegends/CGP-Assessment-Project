#pragma once

#include "cGameObject.h"

class cCharacter : public cGameObject
{
public:
	cCharacter(sEssentials* required);

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;
};

