#pragma once
#include "actor.h"

class Ship : public Actor {
public:
    Ship(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessKeyboard();
    float GetRightSpeed() const { return mRightSpeed; }
    float GetDownSpeed() const { return mDownSpeed; }

private:
    float mRightSpeed;
    float mDownSpeed;
};
