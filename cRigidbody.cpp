#include "cRigidbody.h"

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
	m_acceleration.m_x = m_force.m_x / m_mass;
	m_acceleration.m_y = m_gravity + m_force.m_y / m_mass;

	m_velocity = m_acceleration * deltaTime;
	m_position = m_velocity * deltaTime;
}

void cRigidbody::UseForceMode(cVector2 force, float dt, ForceMode mode)
{
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
