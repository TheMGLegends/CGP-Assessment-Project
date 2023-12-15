#include <iostream>

#include "cTransform.h"

cTransform::cTransform(float x, float y) : m_x{ x }, m_y{ y }
{
}

void cTransform::DisplayPosition() const
{
	std::cout << "( X: " << m_x << ", Y: " << m_y << " )" << std::endl;
}
