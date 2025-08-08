#pragma once
#include "game_math.h"
#include <random>

class GameRandom {
public:
    static void Init();
    static void Seed(unsigned int seed);
    static float GetFloatRange(float min, float max);
    static float GetFloat();
    static Vector2 GetVector(const Vector2& min, const Vector2& max);

private:
    static std::mt19937 sGenerator;
};
