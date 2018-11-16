#ifndef Vector2D_h
#define Vector2D_h
#include <cmath>

class Vector2D
{
public:
	Vector2D(float x, float y) : x(x), y(y) {}
	float GetX() { return this->x; }
	float GetY() { return this->y; }
	void SetX(float x) { this->x = x; }
	void SetY(float y) { this->y = y; }

	Vector2D operator+(const Vector2D& v2) const
	{
		return Vector2D(x + v2.x, y + v2.y);
	}
	//friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
	//{
	//	v1.x += v2.x;
	//	v1.y += v2.y;
	//	return v1;
	//}
	Vector2D& operator+=(const Vector2D& v2)
	{
		x += v2.x;
		y += v2.y;
		return *this;
	}

	Vector2D operator-(const Vector2D& v2) const
	{
		return Vector2D(x - v2.x, y - v2.y);
	}
	//friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
	//{
	//	v1.x -= v2.x;
	//	v1.y -= v2.y;
	//	return v1;
	//}
	Vector2D& operator-=(const Vector2D& v2)
	{
		x -= v2.x;
		y -= v2.y;
		return *this;
	}

	Vector2D operator*(const float& scalar) const
	{
		return Vector2D(x * scalar, y * scalar);
	}
	Vector2D& operator*=(const float& scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Vector2D operator/(const float& scalar) const
	{
		return Vector2D(x / scalar, y / scalar);
	}
	Vector2D& operator/=(const float& scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}

	float Length() const
	{
		return sqrt(x * x + y * y);
	}

	Vector2D& Normalize()
	{
		return *this /= Length();
	}

private:
	float x;
	float y;
};

#endif