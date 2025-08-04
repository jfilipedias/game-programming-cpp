#pragma once

namespace Math {
const float Pi = 3.1415926535f;

inline float ToRadians(float degrees) {
    return degrees * Pi / 180.0f;
}

inline float ToDegrees(float radians) {
    return radians * 180.0f / Pi;
}
} // namespace Math

class Vector2 {
public:
    float x;
    float y;

    Vector2()
        : x{ 0.0f },
          y{ 0.0f } {}

    explicit Vector2(float inX, float inY)
        : x{ inX },
          y{ inY } {}

    static const Vector2 Zero;
};
