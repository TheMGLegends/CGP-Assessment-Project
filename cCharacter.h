#pragma once

#include "cAnimator.h"
#include "cBoxCollider.h"
#include "cGameObject.h"

enum class CharacterType 
{
	None,
	Player,
	Goomba,
	BulletBill
};

class cCharacter : public cGameObject
{
public:
	cCharacter(sEssentials* required);

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Clean() = 0;

	inline cBoxCollider* GetBoxCollider() const { return m_boxCollider; }
	inline bool GetIsDead() const { return m_bIsDead; }

	inline void SetIsDead(bool isDead) { m_bIsDead = isDead; }

protected:
	cTransform* m_previousPosition;
	cTransform* m_startingPosition;

	cAnimator* m_animator;
	cBoxCollider* m_boxCollider;

	CharacterType m_characterType;
	bool m_bIsDead;
};

