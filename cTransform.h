#pragma once

#include "cVector2.h"

// INFO: The following was used as a reference: https://docs.unity3d.com/ScriptReference/Vector2.html

class cTransform
{
public:
	// INFO: Position
	float m_x;
	float m_y;

	cTransform(float x = 0, float y = 0);

	// INFO: Testing Functionality
	void DisplayPosition() const;

private:
	// Don't know whether to keep or not --------------------------------------------------------------------------------------
	inline void TranslateX(float x) { m_x += x; }
	inline void TranslateY(float y) { m_y += y; }
	inline void Translate(cVector2 vector) { m_x += vector.m_x; m_y += vector.m_y; }
};

