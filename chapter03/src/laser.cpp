#include "laser.h"
#include "asteroid.h"
#include "circle_component.h"
#include "game.h"
#include "move_component.h"
#include "sprite_component.h"

Laser::Laser(Game* game)
    : Actor(game),
      mDeathTimer{ 1.0f } {
    SpriteComponent* sc{ new SpriteComponent{ this } };
    sc->SetTexture(game->GetTexture("assets/laser.png"));

    MoveComponent* mc{ new MoveComponent{ this } };
    mc->SetForwardSpeed(800.0f);

    mCircle = { new CircleComponent{ this } };
    mCircle->SetRadius(11.0f);
}

void Laser::UpdateActor(float deltaTime) {
    mDeathTimer -= deltaTime;
    if (mDeathTimer <= 0.0f) {
        SetState(Actor::EDead);
        return;
    }

    for (Asteroid* ast : GetGame()->GetAsteroids()) {
        if (Intersect(*mCircle, *(ast->GetCircle()))) {
            SetState(Actor::EDead);
            ast->SetState(Actor::EDead);
            break;
        }
    }
}