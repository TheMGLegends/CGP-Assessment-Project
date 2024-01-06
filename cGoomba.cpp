#include "cCamera.h"
#include "cCollisionManager.h"
#include "sGlobalStrings.h"

#include "cGoomba.h"

#include "MemoryLeakDetector.h"

cGoomba::cGoomba(sEssentials* required) : cCharacter(required)
{
	m_characterType = CharacterType::Goomba;
	m_walkingDirection = LEFT;

	m_animator->SetAnimation(sGlobalStrings::Goomba_Walk, 0, 2, 100, 2);
	m_movementSpeed = 2.5f;
}

void cGoomba::Update(float deltaTime)
{
	if (!m_bIsDead && m_position->m_x < cCamera::Instance()->GetPosition().m_x + cCamera::Instance()->GetCameraView().w)
	{
		m_rb2D->AddForceX(m_walkingDirection * m_movementSpeed, deltaTime);
		m_animator->SetAnimation(sGlobalStrings::Goomba_Walk, 0, 2, 100, 2);
	}
	else if (m_bIsDead)
	{
		m_rb2D->CancelForceX();
		m_animator->SetAnimation(sGlobalStrings::Goomba_Death, 0, 1, 100, 2);
	}

	m_rb2D->Update(deltaTime);

	m_previousPosition->m_x = m_position->m_x;
	m_position->TranslateX(m_rb2D->GetPosition().m_x);
	m_boxCollider->UpdateCollider(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), static_cast<int>(m_width * 2.0f), static_cast<int>(m_height * 1.75f));

	if (cCollisionManager::Instance()->MapCollision(m_boxCollider->GetRect()))
	{
		m_position->m_x = m_previousPosition->m_x;

		// INFO: Ping-pong Effect 
		switch (m_walkingDirection)
		{
		case LEFT:
			m_walkingDirection = RIGHT;
			break;
		case RIGHT:
			m_walkingDirection = LEFT;
			break;
		default:
			break;
		}
	}

	m_previousPosition->m_y = m_position->m_y;
	m_position->TranslateY(m_rb2D->GetPosition().m_y);
	m_boxCollider->UpdateCollider(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), static_cast<int>(m_width * 2.0f), static_cast<int>(m_height * 1.75f));


	if (cCollisionManager::Instance()->MapCollision(m_boxCollider->GetRect()))
		m_position->m_y = m_previousPosition->m_y;


	m_centerPoint->m_x = m_position->m_x + m_width / 2.0f;
	m_centerPoint->m_y = m_position->m_y + m_height / 2.0f;

	m_animator->Update();
}

void cGoomba::Draw()
{
	m_animator->Draw(static_cast<int>(m_position->m_x), static_cast<int>(m_position->m_y), m_width, m_height);

	m_boxCollider->DrawBoxCollider();
}

void cGoomba::Reset()
{
	m_rb2D->CancelForce();

	m_walkingDirection = LEFT;
	m_position->m_x = m_startingPosition->m_x;
	m_position->m_y = m_startingPosition->m_y;

	m_bIsDead = false;
}
