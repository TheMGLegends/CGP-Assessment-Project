#pragma once

#include "cRigidbody.h"
#include "cCharacter.h"

const float JUMP_INTERVAL = 1.5f;

class cPlayer : public cCharacter
{
public:
	cPlayer(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Clean() override;

private:
	cRigidbody* m_rb2D;

	bool m_bIsGrounded;
	bool m_bIsJumping;

	float m_jumpForce;
	float m_jumpTime;

};

