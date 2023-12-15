#pragma once

// INFO: The following was used as a reference: https://docs.unity3d.com/ScriptReference/Vector2.html

class cVector2
{
public:
	// INFO: Coordinates
	float m_x;
	float m_y;

	// INFO: Directional Vectors
	static const cVector2 DOWN;
	static const cVector2 UP;
	static const cVector2 LEFT;
	static const cVector2 RIGHT;
	static const cVector2 ZERO;

	cVector2(float x = 0, float y = 0);

	static cVector2 Lerp(cVector2 a, cVector2 b, float t);
	static float Distance(cVector2 a, cVector2 b);

	// INFO: Operator Overloads
	cVector2 operator+(const cVector2& other) const;
	cVector2 operator-(const cVector2& other) const;

	// INFO: Dividing and Multiplying works for both vector and scalar values
	cVector2 operator/(const cVector2& other) const;
	cVector2 operator/(const float scalar) const;

	cVector2 operator*(const cVector2& other) const;
	cVector2 operator*(const float scalar) const;

	cVector2& operator+=(const cVector2& other);
	cVector2& operator-=(const cVector2& other);
	cVector2& operator/=(const cVector2& other);
	cVector2& operator*=(const cVector2& other);

	cVector2& operator=(const cVector2& other);
	bool operator==(const cVector2& other) const;
	bool operator!=(const cVector2& other) const;

	float Magnitude();
	cVector2 normalized();
	void Normalize();

	// INFO: Testing Functionality
	void DisplayVector() const;

private:
	static float Clamp(float num, float min, float max);
};