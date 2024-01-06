#include "cGameObject.h"

#include "MemoryLeakDetector.h"

cGameObject::cGameObject(sEssentials* required)
	: m_width(required->_width)
	, m_height(required->_height)
	, m_textureKey(required->_textureKey)
	, m_flip(required->_flip)
{
	m_position = new cTransform(required->_x, required->_y);

	m_centerPoint = new cTransform(m_position->m_x + m_width / 2, m_position->m_y + m_height / 2);

	// INFO: The required values are deleted once they have been assigned
	if (required != nullptr)
	{
		delete required;
		required = nullptr;
	}
}

void cGameObject::Clean()
{
	if (m_centerPoint != nullptr)
	{
		delete m_centerPoint;
		m_centerPoint = nullptr;
	}

	if (m_position != nullptr)
	{
		delete m_position;
		m_position = nullptr;
	}
}
