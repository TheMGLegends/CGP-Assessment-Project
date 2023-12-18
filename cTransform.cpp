#include <iostream>

#include "cTransform.h"

cTransform::cTransform(float x, float y) : m_x{ x }, m_y{ y }
{
}

bool cTransform::operator==(const cTransform& other) const
{
	return (this->m_x == other.m_x) && (this->m_y == other.m_y);
}

bool cTransform::operator!=(const cTransform& other) const
{
	return (this->m_x != other.m_x) || (this->m_y != other.m_y);
}

void cTransform::DisplayPosition() const
{
	std::cout << "( X: " << m_x << ", Y: " << m_y << " )" << std::endl;
}
