#include "cCharacter.h"

cCharacter::cCharacter(sEssentials* required) : cGameObject(required)
{
	m_previousPosition = new cTransform();
	m_animator = new cAnimator();
	m_boxCollider = new cBoxCollider();
}
