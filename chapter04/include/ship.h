#pragma once
#include "actor.h"
#include "circle_component.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ActorInput(const bool* keyState) override;

private:
    CircleComponent* mCircle;
    float mLaserCooldown;
    float mRespawnCooldown;
};