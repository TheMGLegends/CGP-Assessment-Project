#include "cRigidbody.h"

#include "MemoryLeakDetector.h"

cRigidbody::cRigidbody()
	: m_drag{ 0 }
	, m_mass{ BASE_MASS }
	, m_gravity{ BASE_GRAVITY }
	, m_force{}
	, m_acceleration{}
	, m_velocity{}
	, m_position{}
{
}

void cRigidbody::Update(float deltaTime)
{
	// INFO: Uses the principle of "F = M * A" -> "A = F / M" to calculate acceleration in both the x and y axis
	m_acceleration.m_x = m_force.m_x / m_mass;
	m_acceleration.m_y = m_gravity + m_force.m_y / m_mass;

	// INFO: Velocity is then updated accordingly using the principle of "V = A * T"
	m_velocity = m_acceleration * deltaTime;

	// INFO: Position (Displacement) is then updated according to the principle of "D = V * T"
	m_position = m_velocity * deltaTime;
}

void cRigidbody::UseForceMode(cVector2 force, float dt, ForceMode mode)
{
	// INFO: Based on the force mode provided by the user a different force "effect" is achieved
	switch (mode)
	{
	case ForceMode::Force:
		m_force = force * dt / m_mass;
		break;
	case ForceMode::Acceleration:
		m_force = force * dt;
		break;
	case ForceMode::Impulse:
		m_force = force / m_mass;
		break;
	case ForceMode::VelocityChange:
		m_force = force;
		break;
	default:
		break;
	}
}
