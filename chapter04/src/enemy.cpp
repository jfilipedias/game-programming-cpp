#include "enemy.h"
#include "circle_component.h"
#include "game.h"
#include "grid.h"
#include "nav_component.h"
#include "sprite_component.h"
#include "tile.h"

Enemy::Enemy(Game* game)
    : Actor{ game } {
    game->GetEnemies().push_back(this);

    SpriteComponent* sc = new SpriteComponent(this);
    sc->SetTexture(game->GetTexture("assets/airplane.png"));

    Tile* startTile{ game->GetGrid()->GetStartTile() };
    SetPosition(startTile->GetPosition());

    NavComponent* nc = new NavComponent(this);
    nc->SetForwardSpeed(150.0f);
    nc->StartPath(startTile);

    mCircleComp = new CircleComponent{ this };
    mCircleComp->SetRadius(25.0f);
}

Enemy::~Enemy() {
    std::vector<Enemy*>::iterator iter{ std::find(
        GetGame()->GetEnemies().begin(),
        GetGame()->GetEnemies().end(), this) };

    GetGame()->GetEnemies().erase(iter);
}

void Enemy::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    Vector2 distToEndTile{ GetPosition() - GetGame()->GetGrid()->GetEndTile()->GetPosition() };
    if (GameMath::NearZero(distToEndTile.Length(), 10.0f)) {
        SetState(EDead);
    }
}
