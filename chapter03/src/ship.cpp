#include "ship.h"
#include "game.h"
#include "input_component.h"
#include "laser.h"
#include "sprite_component.h"

Ship::Ship(Game* game)
    : Actor{ game },
      mLaserCooldown{ 0.0f } {
    SpriteComponent* sc{ new SpriteComponent{ this } };
    sc->SetTexture(game->GetTexture("assets/ship.png"));

    InputComponent* ic{ new InputComponent{ this } };
    ic->SetForwardKey(SDL_SCANCODE_W);
    ic->SetBackKey(SDL_SCANCODE_S);
    ic->SetClockwiseKey(SDL_SCANCODE_A);
    ic->SetCounterClockwiseKey(SDL_SCANCODE_D);
    ic->SetMaxForwardSpeed(300.0f);
    ic->SetMaxAngularSpeed(GameMath::TwoPi);
}

void Ship::UpdateActor(float deltaTime) {
    mLaserCooldown -= deltaTime;
}

void Ship::ActorInput(const bool* keyState) {
    if (keyState[SDL_SCANCODE_SPACE] && mLaserCooldown <= 0.0f) {
        Laser* laser{ new Laser{ GetGame() } };
        laser->SetPosition(GetPosition());
        laser->SetRotation(GetRotation());

        mLaserCooldown = 0.5f;
    }
}
