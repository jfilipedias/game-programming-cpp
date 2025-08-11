#pragma once
#include "actor.h"
#include "circle_component.h"

class Asteroid : public Actor {
public:
    Asteroid(class Game* game);
    ~Asteroid();

private:
    CircleComponent* mCircle;
};
