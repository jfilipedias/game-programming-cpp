#pragma once
#include "actor.h"
#include "circle_component.h"

class Laser : public Actor {
public:
    Laser(class Game* game);

    void UpdateActor(float deltaTime) override;

private:
    CircleComponent* mCircle;
    float mDeathTimer;
};