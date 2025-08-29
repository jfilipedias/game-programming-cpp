#pragma once
#include "actor.h"

class Tower : public Actor {
public:
    Tower(class Game* game);
    void UpdateActor(float deltaTime) override;

private:
    class MoveComponent* mMoveComp;
    float mNextAttack;
    const float mAttackTime{ 2.5f };
    const float mAttackRange{ 100.0f };
};
