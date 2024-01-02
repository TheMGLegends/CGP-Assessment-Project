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

	inline void AddForce(cVector2 force, float dt, ForceMode mode = ForceMode::Force) { UseForceMode(force, dt, mode); }
	inline void AddForce(float x, float y, float dt, ForceMode mode = ForceMode::Force) { UseForceMode(cVector2(x, y), dt, mode); }

	inline void AddForceX(float x, float dt, ForceMode mode = ForceMode::Force) { UseForceMode(cVector2(x, m_force.m_y), dt, mode); }
	inline void AddForceY(float y, float dt, ForceMode mode = ForceMode::Force) { UseForceMode(cVector2(m_force.m_x, y), dt, mode); }
	
	inline void CancelForce() { m_force = cVector2::ZERO; }
	inline void CancelForceX() { m_force.m_x = cVector2::ZERO.m_x; }
	inline void CancelForceY() { m_force.m_y = cVector2::ZERO.m_y; }

	void Update(float deltaTime);

private:
	float m_drag;
	float m_mass;
	float m_gravity;

	cVector2 m_force;
	cVector2 m_acceleration;
	cVector2 m_velocity;

	cVector2 m_position;

	void UseForceMode(cVector2 force, float dt, ForceMode mode = ForceMode::Force);
};

