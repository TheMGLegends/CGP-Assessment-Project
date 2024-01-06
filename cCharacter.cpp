#include "cCharacter.h"

#include "MemoryLeakDetector.h"

cCharacter::cCharacter(sEssentials* required) : cGameObject(required)
{
	m_rb2D = new cRigidbody();

	m_previousPosition = new cTransform();
	m_startingPosition = new cTransform(m_position->m_x, m_position->m_y);

	m_animator = new cAnimator();
	m_boxCollider = new cBoxCollider();

	m_characterType = CharacterType::None;

	m_bIsDead = false;
	m_movementSpeed = 1.0f;
}

void cCharacter::Clean()
{
	cGameObject::Clean();

	if (m_rb2D != nullptr)
	{
		delete m_rb2D;
		m_rb2D = nullptr;
	}

	if (m_previousPosition != nullptr)
	{
		delete m_previousPosition;
		m_previousPosition = nullptr;
	}

	if (m_startingPosition != nullptr)
	{
		delete m_startingPosition;
		m_startingPosition = nullptr;
	}

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
