#include "cGameObject.h"

cGameObject::cGameObject(sParameters* params)
	: m_width(params->Width)
	, m_height(params->Height)
	, m_flip(params->Flip)
	, m_textureKey(params->TextureKey)
{
	m_position = new cTransform(params->X, params->Y);
}
