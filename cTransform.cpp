#include <iostream>

#include "cTransform.h"

#include "MemoryLeakDetector.h"

cTransform::cTransform(float x, float y) : m_x{ x }, m_y{ y }
{
}

cTransform& cTransform::operator=(const cTransform& other) 
{
	if (this == &other)
		return *this;
	else
	{
		m_x = other.m_x;
		m_y = other.m_y;
		return *this;
	}
}

bool cTransform::operator==(const cTransform& other) const
{
	return (m_x == other.m_x) && (m_y == other.m_y);
}

bool cTransform::operator!=(const cTransform& other) const
{
	return (m_x != other.m_x) || (m_y != other.m_y);
}

void cTransform::DisplayPosition() const
{
	std::cout << "( X: " << m_x << ", Y: " << m_y << " )" << std::endl;
}
