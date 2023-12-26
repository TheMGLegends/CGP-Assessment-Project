#pragma once

#include <iostream>

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

	cVector2(float x = 0, float y = 0) : m_x{ x }, m_y{ y } {};

	static cVector2 Lerp(cVector2 a, cVector2 b, float t);
	static float Distance(cVector2 a, cVector2 b);

	// INFO: Operator Overloads
	inline cVector2 operator+(const cVector2& other) const { return cVector2(m_x + other.m_x, m_y + other.m_y); };
	inline cVector2 operator-(const cVector2& other) const { return cVector2(m_x - other.m_x, m_y - other.m_y); };

	// INFO: Dividing and Multiplying works for both vector and scalar values
	inline cVector2 operator/(const cVector2& other) const { return cVector2(m_x / other.m_x, m_y / other.m_y); };
	inline cVector2 operator/(const float scalar) const { return cVector2(m_x / scalar, m_y / scalar); };

	inline cVector2 operator*(const cVector2& other) const { return cVector2(m_x * other.m_x, m_y * other.m_y); };
	inline cVector2 operator*(const float scalar) const { return cVector2(m_x * scalar, m_y * scalar); };

	cVector2& operator+=(const cVector2& other);
	cVector2& operator-=(const cVector2& other);
	cVector2& operator/=(const cVector2& other);
	cVector2& operator*=(const cVector2& other);

	cVector2& operator=(const cVector2& other);
	inline bool operator==(const cVector2& other) const { return (m_x == other.m_x) && (m_y == other.m_y); };
	inline bool operator!=(const cVector2& other) const { return (m_x != other.m_x) || (m_y != other.m_y); };

	inline float Magnitude() { return float((std::sqrt(std::pow(m_x, 2) + std::pow(m_y, 2)))); };
	cVector2 normalized();
	void Normalize();

	// INFO: Testing Functionality
	inline void DisplayVector() const { std::cout << "( X: " << m_x << ", Y: " << m_y << " )" << std::endl; };

private:
	static float Clamp(float num, float min, float max);
};