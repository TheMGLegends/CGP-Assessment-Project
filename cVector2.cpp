#include "cVector2.h"

#include "MemoryLeakDetector.h"

const cVector2 cVector2::DOWN(0, -1);
const cVector2 cVector2::UP(0, 1);
const cVector2 cVector2::LEFT(-1, 0);
const cVector2 cVector2::RIGHT(1, 0);
const cVector2 cVector2::ZERO(0, 0);

cVector2 cVector2::Lerp(cVector2 a, cVector2 b, float t)
{
	t = Clamp(t, 0, 1);
	return cVector2((a.m_x + b.m_x) * t, (a.m_y + b.m_y) * t);
}

float cVector2::Distance(cVector2 a, cVector2 b)
{
	cVector2 temp(a.m_x - b.m_x, a.m_y - b.m_y);
	return temp.Magnitude();
}

cVector2& cVector2::operator+=(const cVector2& other)
{
	m_x += other.m_x;
	m_y += other.m_y;
	return *this;
}

cVector2& cVector2::operator-=(const cVector2& other)
{
	m_x -= other.m_x;
	m_y -= other.m_y;
	return *this;
}

cVector2& cVector2::operator/=(const cVector2& other)
{
	m_x /= other.m_x;
	m_y /= other.m_y;
	return *this;
}

cVector2& cVector2::operator*=(const cVector2& other)
{
	m_x *= other.m_x;
	m_y *= other.m_y;
	return *this;
}

cVector2& cVector2::operator=(const cVector2& other)
{
	if (this == &other) 
		return *this;
	else {
		m_x = other.m_x;
		m_y = other.m_y;
		return *this;
	}
}

// Returns a new vector of magnitude 1 with the same direction as the vector this was called from.
cVector2 cVector2::normalized()
{
	return cVector2(m_x / Magnitude(), m_y / Magnitude());
}

// Appends the vector this was called from to now have a magnitude of 1, but still retain the same direction.
void cVector2::Normalize()
{
	m_x /= Magnitude();
	m_y /= Magnitude();
}

float cVector2::Clamp(float num, float min, float max)
{
	if (num < min)
		return min;
	else if (num > max)
		return max;
	else
		return num;
}
