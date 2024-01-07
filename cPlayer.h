#pragma once

#include "cPickups.h"
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
	inline bool GetSquishedGoomba() const { return m_bSquishedGoomba; }

	inline void SetSquishedGoomba(bool hasSquishedGoomba) { m_bSquishedGoomba = hasSquishedGoomba; }
	void PickupEffect(PickupType pickupType);

private:
	bool m_bIsGrounded;
	bool m_bIsJumping;
	bool m_bSquishedGoomba;

	bool m_bDeathPlayed;

	float m_jumpForce;
	float m_jumpTime;

	float m_stompedTime;

	int m_score;

	void Move(float deltaTime);
	void Jump(float deltaTime);
};

