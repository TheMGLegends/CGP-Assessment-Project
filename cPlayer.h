#pragma once

#include "cRigidbody.h"

#include "cCharacter.h"

const float JUMP_INTERVAL = 20.0f;
const float STOMP_INTERVAL = 5.0f;

class cPlayer : public cCharacter
{
public:
	cPlayer(sEssentials* required);

	virtual void Update(float deltaTime) override;
	virtual void Draw() override;
	virtual void Reset() override;

	inline bool GetIsGrounded() const { return m_bIsGrounded; }
	inline void SetSquishedGoomba(bool hasSquishedGoomba) { m_bSquishedGoomba = hasSquishedGoomba; }

private:
	bool m_bIsGrounded;
	bool m_bIsJumping;
	bool m_bSquishedGoomba;

	float m_jumpForce;
	float m_jumpTime;

	float m_stompedTime;

	void Move(float deltaTime);
	void Jump(float deltaTime);
};

