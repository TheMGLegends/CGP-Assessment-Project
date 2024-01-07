#pragma once

#include "cAnimator.h"
#include "cBoxCollider.h"

#include "cPickups.h"

class cCoin : public cPickups
{
public:
	cCoin(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Reset() override;
};

