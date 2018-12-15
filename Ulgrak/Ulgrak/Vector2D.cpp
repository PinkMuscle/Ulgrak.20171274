#include "Vector2D.h"
#include <cmath>

Vector2D Vector2D::operator+(const Vector2D& v2) const
{
    return Vector2D(x + v2.x, y + v2.y);
}

Vector2D Vector2D::operator-(const Vector2D& v2) const
{
    return Vector2D(x - v2.x, y - v2.y);
}

Vector2D Vector2D::operator*(const float& scalar) const
{
    return Vector2D(x * scalar, y * scalar);
}

Vector2D operator*(const float& scalar, const Vector2D& v2)
{
    return v2 * scalar;
}

Vector2D Vector2D::operator/(const float& scalar) const
{
    return Vector2D(x / scalar, y / scalar);
}

Vector2D& Vector2D::operator+=(const Vector2D& v2)
{
    x += v2.x;
    y += v2.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& v2)
{
    x -= v2.x;
    y -= v2.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const float& scalar)
{
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2D& Vector2D::operator/=(const float& scalar)
{
    x /= scalar;
    y /= scalar;
    return *this;
}

float Vector2D::Length() const
{
    return sqrt(x * x + y * y);
}

Vector2D& Vector2D::Normalize()
{
    float len = Length();
    if (len == 0.0f)
    {
        return *this;
    }
    else
    {
        return *this /= len;
    }
}

Vector2D Vector2D::Normalized() const
{
    float len = Length();
    if (len == 0.0f)
    {
        return *this;
    }
    else
    {
        return *this / len;
    }
}

Vector2D& Vector2D::Zero()
{
    x = 0.0f;
    y = 0.0f;
    return *this;
}