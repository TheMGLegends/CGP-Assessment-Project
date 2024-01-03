#include "cCharacter.h"

cCharacter::cCharacter(sEssentials* required) : cGameObject(required)
{
	m_previousPosition = new cTransform();
	m_startingPosition = new cTransform(m_position->m_x, m_position->m_y);

	m_animator = new cAnimator();
	m_boxCollider = new cBoxCollider();

	m_characterType = CharacterType::None;
	m_bIsDead = false;
}
