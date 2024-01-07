#include "cPickups.h"

cPickups::cPickups(sEssentials* required) : cGameObject(required)
{
	m_animator = new cAnimator();
	m_boxCollider = new cBoxCollider();

	m_bIsCollected = false;
	
	m_pickupType = PickupType::None;
}

void cPickups::Clean()
{
	cGameObject::Clean();

	if (m_animator != nullptr)
	{
		delete m_animator;
		m_animator = nullptr;
	}

	if (m_boxCollider != nullptr)
	{
		delete m_boxCollider;
		m_boxCollider = nullptr;
	}
}
