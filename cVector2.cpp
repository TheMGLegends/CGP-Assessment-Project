#include <algorithm>
#include <cmath>
#include <iostream>

#include "cVector2.h"

const cVector2 cVector2::DOWN(0, -1);
const cVector2 cVector2::UP(0, 1);
const cVector2 cVector2::LEFT(-1, 0);
const cVector2 cVector2::RIGHT(1, 0);
const cVector2 cVector2::ZERO(0, 0);

cVector2::cVector2(float x, float y) : m_x{ x }, m_y{ y }
{
}

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

cVector2 cVector2::operator+(const cVector2& other) const
{
	return cVector2(this->m_x + other.m_x, this->m_y + other.m_y);
}

cVector2 cVector2::operator-(const cVector2& other) const
{
	return cVector2(this->m_x - other.m_x, this->m_y - other.m_y);
}

cVector2 cVector2::operator/(const cVector2& other) const
{
	return cVector2(this->m_x / other.m_x, this->m_y / other.m_y);
}

cVector2 cVector2::operator/(const float scalar) const
{
	return cVector2(this->m_x / scalar, this->m_y / scalar);
}

cVector2 cVector2::operator*(const cVector2& other) const
{
	return cVector2(this->m_x * other.m_x, this->m_y * other.m_y);
}

cVector2 cVector2::operator*(const float scalar) const
{
	return cVector2(this->m_x * scalar, this->m_y * scalar);
}

cVector2& cVector2::operator+=(const cVector2& other)
{
	this->m_x += other.m_x;
	this->m_y += other.m_y;
	return *this;
}

cVector2& cVector2::operator-=(const cVector2& other)
{
	this->m_x -= other.m_x;
	this->m_y -= other.m_y;
	return *this;
}

cVector2& cVector2::operator/=(const cVector2& other)
{
	this->m_x /= other.m_x;
	this->m_y /= other.m_y;
	return *this;
}

cVector2& cVector2::operator*=(const cVector2& other)
{
	this->m_x *= other.m_x;
	this->m_y *= other.m_y;
	return *this;
}

cVector2& cVector2::operator=(const cVector2& other)
{
	if (this == &other) 
		return *this;
	else {
		this->m_x = other.m_x;
		this->m_y = other.m_y;
		return *this;
	}
}

bool cVector2::operator==(const cVector2& other) const
{
	return (this->m_x == other.m_x) && (this->m_y == other.m_y);
}

bool cVector2::operator!=(const cVector2& other) const
{
	return (this->m_x != other.m_x) || (this->m_y != other.m_y);
}

float cVector2::Magnitude()
{
	return (std::sqrt(std::pow(m_x, 2) + std::pow(m_y, 2)));
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

void cVector2::DisplayVector() const
{
	std::cout << "( X: " << m_x << ", Y: " << m_y << " )" << std::endl;
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
