#pragma once
#include <cmath>

namespace GameMath {
const float Pi = 3.1415926535f;
const float TwoPi = Pi * 2.0f;
const float PiOver2 = Pi / 2.0f;

inline float ToRadian(float degrees) {
    return degrees * Pi / 180.0f;
}

inline float ToDegrees(float radians) {
    return radians * 180.0f / Pi;
}

inline bool NearZero(float val, float epsilon = 0.001f) {
    return fabs(val) <= epsilon;
}

// X axis == Cosine(θ)
inline float Cos(float angle) {
    return cosf(angle);
}

// Y axis == Sine(θ)
inline float Sin(float angle) {
    return sinf(angle);
}

inline float Tan(float angle) {
    return tanf(angle);
}

inline float Acos(float angle) {
    return acosf(angle);
}

inline float Atan2(float y, float x) {
    return atan2f(y, x);
}

inline float Sqrt(float value) {
    return sqrtf(value);
}
} // namespace GameMath

class Vector2 {
public:
    float x{ 0.0f };
    float y{ 0.0f };

    Vector2()
        : x{ 0.0f },
          y{ 0.0f } {}

    explicit Vector2(float inX, float inY)
        : x{ inX },
          y{ inY } {}

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

    void Normalize() {
        float length{ Length() };
        x /= length;
        y /= length;
    }

    static Vector2 Normalize(const Vector2& vec) {
        Vector2 temp{ vec };
        temp.Normalize();
        return temp;
    }

    // Dot product between two vectors: a · b
    static float Dot(const Vector2& a, const Vector2& b) {
        return a.x * b.x + a.y * b.y;
    }

    static const Vector2 Zero;
    static const Vector2 UnitX;
    static const Vector2 UnitY;
    static const Vector2 NegUnitX;
    static const Vector2 NegUnitY;
};
