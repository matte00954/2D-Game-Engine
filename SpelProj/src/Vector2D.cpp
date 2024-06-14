#include "Vector2D.h"

Vector2D::Vector2D()
{
    x = 0.0f;
    y = 0.0f;
}

// p = parameter
Vector2D::Vector2D(float newX, float newY)
{
    x = newX;
    y = newY;
}

Vector2D &Vector2D::add(const Vector2D &vec)
{
    x += vec.x;
    y += vec.y;

    return *this;
}

Vector2D &Vector2D::subtract(const Vector2D &vec)
{
    x -= vec.x;
    y -= vec.y;

    return *this;
}

Vector2D &Vector2D::multiply(const Vector2D &vec)
{
    x *= vec.x;
    y *= vec.y;

    return *this;
}

Vector2D &Vector2D::divide(const Vector2D &vec)
{

    x /= vec.x;
    y /= vec.y;

    return *this;
}

Vector2D &operator+(Vector2D &vec1, const Vector2D &vec2)
{
    return vec1.add(vec2);
}

Vector2D &operator-(Vector2D &vec1, const Vector2D &vec2)
{
    return vec1.subtract(vec2);
}

Vector2D &operator*(Vector2D &vec1, const Vector2D &vec2)
{
    return vec1.multiply(vec2);
}

Vector2D &operator/(Vector2D &vec1, const Vector2D &vec2)
{
    return vec1.divide(vec2);
}

Vector2D &Vector2D::operator+=(const Vector2D vec)
{
    return this->add(vec);
}

Vector2D &Vector2D::operator-=(const Vector2D vec)
{
    return this->subtract(vec);
}

Vector2D &Vector2D::operator*=(const Vector2D vec)
{
    return this->multiply(vec);
}

Vector2D &Vector2D::operator/=(const Vector2D vec)
{
    return this->divide(vec);
}

Vector2D &Vector2D::zero()
{
    this->x = 0;
    this->y = 0;
    return *this;
}

Vector2D &Vector2D::operator*(const int &i)
{
    this->x *= i;
    this->y *= i;
    return *this;
}

std::ostream &operator<<(std::ostream &os, const Vector2D &vec)
{
    os << "Vector2D(x,y) : ("
       << vec.x << "," << vec.y << ")";
    return os;
}