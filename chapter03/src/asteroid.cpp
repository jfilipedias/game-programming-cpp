#include "asteroid.h"
#include "game.h"
#include "game_random.h"
#include "move_component.h"
#include "sprite_component.h"

Asteroid::Asteroid(Game* game)
    : Actor{ game } {
    Vector2 randPos{ GameRandom::GetVector(Vector2::Zero, Vector2{ 1024.0f, 768.0f }) };
    SetPosition(randPos);
    SetRotation(GameRandom::GetFloatRange(0.0f, GameMath::TwoPi));

    SpriteComponent* sc{ new SpriteComponent{ this } };
    sc->SetTexture(game->GetTexture("assets/asteroid.png"));

    MoveComponent* mc{ new MoveComponent{ this } };
    mc->SetForwardSpeed(150.0f);

    mCircle = new CircleComponent{ this };
    mCircle->SetRadius(40.0f);
}
