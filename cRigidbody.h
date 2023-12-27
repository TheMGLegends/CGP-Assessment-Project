#pragma once

#include "cVector2.h"

// INFO: The following was used as a reference: https://docs.unity3d.com/ScriptReference/Rigidbody.html

const float BASE_MASS = 1.0f;
const float BASE_GRAVITY = 9.8f;

enum class ForceMode 
{
	Force,
	Acceleration,
	Impulse,
	VelocityChange
};

class cRigidbody
{
public:
	cRigidbody();

	inline void SetGravity(float gravity) { m_gravity = gravity; }
	inline void SetMass(float mass) { m_mass = mass; }

	inline cVector2 GetAcceleration() const { return m_acceleration; }
	inline cVector2 GetVelocity() const { return m_velocity; }
	inline cVector2 GetPosition() const { return m_position; }

	// _____ dt value may be temporary and may not be necessary to pass once time class is created
	inline void AddForce(cVector2 force, ForceMode mode, float dt) { UseForceMode(force, mode, dt); }
	inline void AddForce(float x, float y, ForceMode mode, float dt) { UseForceMode(cVector2(x, y), mode, dt); }
	inline void CancelForce() { m_force = cVector2::ZERO; }

	void Update(float deltaTime);

private:
	float m_drag;
	float m_mass;
	float m_gravity;

	cVector2 m_force;
	cVector2 m_acceleration;
	cVector2 m_velocity;

	cVector2 m_position;

	void UseForceMode(cVector2 force, ForceMode mode, float dt);
};

