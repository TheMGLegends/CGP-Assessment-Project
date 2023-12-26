#include "cCharacter.h"

cCharacter::cCharacter(sEssentials* required) : cGameObject(required)
{
	m_animator = new cAnimator();
}
