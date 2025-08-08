#pragma once
#include "actor.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const bool* keyState) override;

private:
    float mLaserCooldown;
};