#include "tower.h"
#include "bullet.h"
#include "enemy.h"
#include "game.h"
#include "move_component.h"
#include "sprite_component.h"

Tower::Tower(Game* game)
    : Actor{ game } {
    SpriteComponent* sc = new SpriteComponent{ this, 200 };
    sc->SetTexture(game->GetTexture("assets/tower.png"));

    mMoveComp = new MoveComponent(this);
    mNextAttack = mAttackTime;
}

void Tower::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    mNextAttack -= deltaTime;
    if (mNextAttack > 0.0f) {
        return;
    }

    mNextAttack += mAttackTime;

    Enemy* e = GetGame()->GetNearestEnemy(GetPosition());
    if (e == nullptr) {
        return;
    }

    Vector2 dir{ e->GetPosition() - GetPosition() };
    float dist{ dir.Length() };

    if (dist >= mAttackRange) {
        return;
    }

    // Face the enemy
    SetRotation(GameMath::Atan2(-dir.y, dir.x));
    Bullet* b = new Bullet{ GetGame() };
    b->SetPosition(GetPosition());
    b->SetRotation(GetRotation());
}
