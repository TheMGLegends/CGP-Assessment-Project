#pragma once

#include "cAnimator.h"
#include "cBoxCollider.h"
#include "cGameObject.h"
#include "cRigidbody.h"

// INFO: Represent which way you a character is travelling
const int UP = -1;
const int DOWN = 1;
const int LEFT = -1;
const int RIGHT = 1;

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
	virtual void Reset() = 0;
	virtual void Clean() override;

	inline cBoxCollider* GetBoxCollider() const { return m_boxCollider; }
	inline bool GetIsDead() const { return m_bIsDead; }
	inline cRigidbody* GetRigidBody() const { return m_rb2D; }

	inline void SetIsDead(bool isDead) { m_bIsDead = isDead; }

protected:
	cRigidbody* m_rb2D;

	cTransform* m_previousPosition;
	cTransform* m_startingPosition;

	cAnimator* m_animator;
	cBoxCollider* m_boxCollider;

	CharacterType m_characterType;

	bool m_bIsDead;
	float m_movementSpeed;
};

