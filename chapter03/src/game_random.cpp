#include "game_random.h"

void GameRandom::Init() {
    std::random_device rd;
    GameRandom::Seed(rd());
}

void GameRandom::Seed(unsigned int seed) {
    sGenerator.seed(seed);
}

float GameRandom::GetFloatRange(float min, float max) {
    std::uniform_real_distribution<float> dist{ min, max };
    return dist(sGenerator);
}

float GameRandom::GetFloat() {
    return GetFloatRange(0.0f, 1.0f);
}

Vector2 GameRandom::GetVector(const Vector2& min, const Vector2& max) {
    Vector2 rand{ GetFloat(), GetFloat() };
    return min + (max - min) * rand;
}
