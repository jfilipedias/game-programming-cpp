#pragma once
#include <cmath>

namespace GameMath {
const float Pi = 3.1415926535f;

inline float ToDegrees(float radians) {
    return radians * 180.0f / Pi;
}

inline float Sqrt(float value) {
    return sqrtf(value);
}
} // namespace GameMath

class Vector2 {
public:
    float x{ 0.0f };
    float y{ 0.0f };

    Vector2(float x, float y)
        : x{ x },
          y{ y } {}

    // Vector addition: a + b
    friend Vector2 operator+(const Vector2& a, const Vector2& b) {
        return Vector2{ a.x + b.x, a.y + b.y };
    }

    // Vector subtraction: a - b
    friend Vector2 operator-(const Vector2& a, const Vector2& b) {
        return Vector2{ a.x - b.x, a.y - b.y };
    }

    // Component-wise multiplication: a * b
    friend Vector2 operator*(const Vector2& a, const Vector2& b) {
        return Vector2{ a.x * b.x, a.y * b.y };
    }

    // Scalar multiplication: 5.0f * vec
    friend Vector2 operator*(float scalar, const Vector2& vec) {
        return Vector2{ scalar * vec.x, scalar * vec.y };
    }

    // Scalar multiplication: vec * 5.0f
    friend Vector2 operator*(const Vector2& vec, float scalar) {
        return Vector2{ scalar * vec.x, scalar * vec.y };
    }

    // Vector addition +=
    Vector2& operator+=(const Vector2& vec) {
        x += vec.x;
        y += vec.y;
        return *this;
    }

    // Vector subtraction -=
    Vector2& operator-=(const Vector2& vec) {
        x -= vec.x;
        y -= vec.y;
        return *this;
    }

    // Scalar multiplication *=
    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    float LengthSquared() const {
        return x * x + y * y;
    }

    float Length() const {
        return GameMath::Sqrt(LengthSquared());
    }

    float Normalize() {
        float length{ Length() };
        x /= length;
        y /= length;
    }

    static Vector2 Normalize(const Vector2& vec) {
        Vector2 temp{ vec };
        temp.Normalize();
        return temp;
    }

    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 NegUnitX;
    static const Vector2 NegUnitY;
};
