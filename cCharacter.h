#pragma once

#include "cAnimator.h"
#include "cBoxCollider.h"
#include "cGameObject.h"

class cCharacter : public cGameObject
{
public:
	cCharacter(sEssentials* required);

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;

protected:
	cTransform* m_previousPosition;

	cAnimator* m_animator;
	cBoxCollider* m_boxCollider;
};

