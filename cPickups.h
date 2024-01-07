#pragma once

#include "cAnimator.h"
#include "cBoxCollider.h"

#include "cGameObject.h"

enum class PickupType
{
	None,
	Coin,
};

class cPickups : public cGameObject
{
public:
	cPickups(sEssentials* required);

	virtual void Update(float deltaTime) = 0;
	virtual void Draw() = 0;
	virtual void Reset() = 0;
	virtual void Clean() override;

	inline cBoxCollider* GetBoxCollider() const { return m_boxCollider; }
	inline bool GetIsCollected() const { return m_bIsCollected; }
	inline PickupType GetPickupType() const { return m_pickupType; }

	inline void SetIsCollected(bool isCollected) { m_bIsCollected = isCollected; }

protected:
	cAnimator* m_animator;
	cBoxCollider* m_boxCollider;

	bool m_bIsCollected;
	PickupType m_pickupType;
};

