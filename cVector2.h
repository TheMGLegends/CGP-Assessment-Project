#pragma once

//https://docs.unity3d.com/ScriptReference/Vector2.html Use this for reference
class cVector2
{
public:
	static const cVector2 DOWN;
	static const cVector2 UP;
	static const cVector2 LEFT;
	static const cVector2 RIGHT;
	static const cVector2 ZERO;

	cVector2(float x, float y);
	~cVector2();

	static cVector2 Lerp(cVector2 a, cVector2 b, float t);
	static float Distance(cVector2 a, cVector2 b);

	cVector2 operator+(const cVector2& other) const;
	cVector2 operator-(const cVector2& other) const;
	cVector2 operator/(const cVector2& other) const;
	cVector2 operator*(const cVector2& other) const;

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

protected:
	float m_x;
	float m_y;

private:
	static float Clamp(float num, float min, float max);
};