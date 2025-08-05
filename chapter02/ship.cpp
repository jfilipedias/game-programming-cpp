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
