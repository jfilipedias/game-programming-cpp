#pragma once
#include "actor.h"

class Enemy : public Actor {
public:
    Enemy(class Game* game);
    ~Enemy();
    void UpdateActor(float deltaTime) override;
    class CircleComponent* GetCircleComponent() { return mCircleComp; }

private:
    class CircleComponent* mCircleComp;
};