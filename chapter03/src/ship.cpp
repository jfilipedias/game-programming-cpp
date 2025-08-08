#include "ship.h"
#include "game.h"
#include "sprite_component.h"

Ship::Ship(Game* game)
    : Actor{ game },
      mLaserCooldown{ 0.0f } {
    SpriteComponent* sc{ new SpriteComponent{ this } };
    sc->SetTexture(game->GetTexture("assets/ship.png"));
}
