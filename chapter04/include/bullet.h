#pragma once
#include "actor.h"

class Bullet : public Actor {
public:
    Bullet(class Game* game);
    void UpdateActor(float deltaTime) override;

private:
    class CircleComponent* mCircleComp;
    float mLiveTime;
};
