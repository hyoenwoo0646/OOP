#pragma once

#include <cmath>

class Vector2 {
    float x;
    float y;

public:
    Vector2(float x=0.0f, float y=0.0f) : x(x), y(y) {}

    double magnitude() {
        return sqrt(x*x + y*y);
    }

    double sqrMagnitude() {
        return x*x + y*y;
    }

    static Vector2 one;
    static Vector2 zero;
    static Vector2 up;
    static Vector2 down;
    static Vector2 left;
    static Vector2 right;
};

