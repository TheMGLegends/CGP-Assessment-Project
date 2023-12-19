#include "cGameObject.h"

cGameObject::cGameObject(sEssentials* required)
	: m_width(required->_width)
	, m_height(required->_height)
	, m_textureKey(required->_textureKey)
	, m_flip(required->_flip)
{
	m_position = new cTransform(required->_x, required->_y);
}
