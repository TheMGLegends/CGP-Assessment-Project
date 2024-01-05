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
}

void cCharacter::Clean()
{
	cGameObject::Clean();

	if (m_rb2D != nullptr)
	{
		delete m_rb2D;
	}
}
