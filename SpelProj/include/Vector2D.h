#ifndef __VECTOR2D_H__
#define __VECTOR2D_H__
#include <iostream>

//Pattern Vector2
class Vector2D
{
public:
    Vector2D();
    Vector2D(float x, float y);

    //these variables are public in order to change them easily
    //for example player : Vector2D (represents velocity) vector.x = 6
    //instead of complex sets/gets
    float x;
    float y;

    // calculations
    Vector2D &add(const Vector2D &vec);
    Vector2D &subtract(const Vector2D &vec);
    Vector2D &multiply(const Vector2D &vec);
    Vector2D &divide(const Vector2D &vec);

    // basic operators
    friend Vector2D &operator+(Vector2D &vec1, const Vector2D &vec2);
    friend Vector2D &operator-(Vector2D &vec1, const Vector2D &vec2);
    friend Vector2D &operator*(Vector2D &vec1, const Vector2D &vec2);
    friend Vector2D &operator/(Vector2D &vec1, const Vector2D &vec2);

    // assignment operators
    Vector2D &operator+=(const Vector2D vec);
    Vector2D &operator-=(const Vector2D vec);
    Vector2D &operator*=(const Vector2D vec);
    Vector2D &operator/=(const Vector2D vec);

    Vector2D &operator*(const int &i);
    Vector2D &zero();

    friend std::ostream &operator<<(std::ostream &os, const Vector2D &vec);
};
#endif // __VECTOR2D_H__