#pragma once

#include "cCharacter.h"

class cGoomba : public cCharacter
{
public:
	cGoomba(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Clean() override;

	void Reset();
private:
	int m_walkingDirection;
};

