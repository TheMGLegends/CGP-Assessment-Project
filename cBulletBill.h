#pragma once
#include "cCharacter.h"
class cBulletBill : public cCharacter
{
public:
	cBulletBill(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Clean() override;

	void Reset();
private:
};

