#include "sGlobalStrings.h"

#include "cCoin.h"

#include "MemoryLeakDetector.h"

cCoin::cCoin(sEssentials* required) : cPickups(required)
{
	m_animator->SetAnimation(sGlobalStrings::Coin_Rotating, 0, 4, 75, 2);

	m_pickupType = PickupType::Coin;
}

void cCoin::Update(float deltaTime)
{
	m_boxCollider->UpdateCollider(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), static_cast<int>(m_width * 2.0f), static_cast<int>(m_height * 2.0f));
	m_animator->Update();
}

void cCoin::Draw()
{
	if (m_bIsCollected)
		m_animator->Draw(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), 0, 0);
	else
		m_animator->Draw(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), m_width, m_height);

	//m_boxCollider->DrawBoxCollider();
}

void cCoin::Reset()
{
	m_bIsCollected = false;
}
