#pragma once

#include "cCharacter.h"

const int STAY_INTERVAL = 5.0f;

class cGoomba : public cCharacter
{
public:
	cGoomba(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Clean() override;
	virtual void Reset() override;

private:
	int m_walkingDirection;
};

