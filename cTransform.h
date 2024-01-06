#pragma once

#include "cVector2.h"

// INFO: The following was used as a reference: https://docs.unity3d.com/ScriptReference/Transform.html

class cTransform
{
public:
	cTransform(float x = 0, float y = 0);

	// INFO: Operator Overloads
	cTransform& operator=(const cTransform& other);
	bool operator==(const cTransform& other) const;
	bool operator!=(const cTransform& other) const;

	// INFO: Used to move an object in a given direction
	inline void TranslateX(float x) { m_x += x; }
	inline void TranslateY(float y) { m_y += y; }
	inline void Translate(cVector2 vector) { m_x += vector.m_x; m_y += vector.m_y; }

	// INFO: Testing Functionality
	void DisplayPosition() const;

	// INFO: Position
	float m_x;
	float m_y;

};

