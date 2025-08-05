#include "ship.h"
#include "anim_sprite_component.h"
#include "game.h"

Ship::Ship(Game* game)
    : Actor{ game },
      mRightSpeed{ 0.0f },
      mDownSpeed{ 0.0f } {
    std::vector<SDL_Texture*> anims{
        game->GetTexture("assets/ship-01.png"),
        game->GetTexture("assets/ship-02.png"),
        game->GetTexture("assets/ship-03.png"),
        game->GetTexture("assets/ship-04.png"),
    };

    AnimSpriteComponent* asc{ new AnimSpriteComponent{ this } };
    asc->SetAnimTextures(anims);
}

void Ship::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    Vector2 pos{ GetPosition() };
    pos.x += mRightSpeed * deltaTime;
    pos.y += mDownSpeed * deltaTime;

    // Restrict position to left half of screen
    if (pos.x < 25.0f) {
        pos.x = 25.0f;
    } else if (pos.x > 500.0f) {
        pos.x = 500.0f;
    }

    if (pos.y < 25.0f) {
        pos.y = 25.0f;
    } else if (pos.y > 743.0f) {
        pos.y = 743.0f;
    }

    SetPosition(pos);
}

void Ship::ProcessKeyboard(const bool* state) {
    mRightSpeed = 0.0f;
    mDownSpeed = 0.0f;

    if (state[SDL_SCANCODE_D]) {
        mRightSpeed += 250.0f;
    }

    if (state[SDL_SCANCODE_A]) {
        mRightSpeed -= 250.0f;
    }

    if (state[SDL_SCANCODE_S]) {
        mDownSpeed += 300.0f;
    }

    if (state[SDL_SCANCODE_W]) {
        mDownSpeed -= 300.0f;
    }
}
