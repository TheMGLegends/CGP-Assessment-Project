#pragma once

#include "cRigidbody.h"
#include "cCharacter.h"

class cPlayer : public cCharacter
{
public:
	cPlayer(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Clean() override;

private:
	cRigidbody* m_rb2D;

};

