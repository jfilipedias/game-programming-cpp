#include "bullet.h"

#include "../../chapter03/include/circle_component.h"
#include "../../chapter03/include/move_component.h"
#include "enemy.h"
#include "game.h"
#include "sprite_component.h"

Bullet::Bullet(Game* game)
    : Actor{ game } {
    SpriteComponent* sc = new SpriteComponent{ this };
    sc->SetTexture(game->GetTexture("assets/projectile.png"));

    MoveComponent* mc = new MoveComponent{ this };
    mc->SetForwardSpeed(400.0f);

    mCircleComp = new MoveComponent{ this };
    mCircleComp->SetRadius(5.0f);

    mLiveTime = 1.0f;
}

void Bullet::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    for (Enemy* e : GetGame()->GetEnemies()) {
        if (Intersect(*mCircleComp, *(e->GetCircleComponent()))) {
            e->SetState(EDead);
            SetState(EDead);
            break;
        }
    }

    mLiveTime -= deltaTime;
    if (mLiveTime <= 0.0f) {
        SetState(EDead);
    }
}
