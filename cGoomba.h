#pragma once

#include "cCharacter.h"

class cGoomba : public cCharacter
{
public:
	cGoomba(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Reset() override;

private:
	int m_walkingDirection;
};

