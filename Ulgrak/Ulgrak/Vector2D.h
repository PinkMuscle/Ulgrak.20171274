#ifndef Vector2D_h
#define Vector2D_h

class Vector2D
{
public:
    float x;
    float y;

    Vector2D() : x(0.0f), y(0.0f) {}
	Vector2D(float x, float y) : x(x), y(y) {}

    Vector2D operator+(const Vector2D& v2) const;
    Vector2D operator-(const Vector2D& v2) const;
    Vector2D operator*(const float& scalar) const;
    friend Vector2D operator*(const float& scalar, const Vector2D& v2);
    Vector2D operator/(const float& scalar) const;

    Vector2D& operator+=(const Vector2D& v2);
    Vector2D& operator-=(const Vector2D& v2);
    Vector2D& operator*=(const float& scalar);
    Vector2D& operator/=(const float& scalar);

    float Length() const;
    Vector2D& Normalize();
    Vector2D Normalized() const;
    Vector2D& Zero();
};

#endif