#include "tile.h"
#include "game.h"
#include "sprite_component.h"

Tile::Tile(Game* game)
    : Actor{ game },
      mParent{ nullptr },
      f{ 0.0f },
      g{ 0.0f },
      h{ 0.0f },
      mBlocked{ false },
      mSprite{ nullptr },
      mTileState{ EDefault },
      mSelected{ false } {
    mSprite = new SpriteComponent{ this };
    UpdateTexture();
}

void Tile::SetTileState(TileState state) {
    mTileState = state;
    UpdateTexture();
}

void Tile::ToggleSelect() {
    mSelected = !mSelected;
    UpdateTexture();
}

void Tile::UpdateTexture() {
    std::string texturePath;
    switch (mTileState) {
    case EStart:
        texturePath = "assets/tile-tan.png";
        break;
    case EBase:
        texturePath = "assets/tile-green.png";
        break;
    case EPath:
        if (mSelected) {
            texturePath = "assets/tile-grey-selected.png";
        } else {
            texturePath = "assets/tile-grey.png";
        }
        break;
    case EDefault:
    default:
        if (mSelected) {
            texturePath = "assets/tile-brown-selected.png";
        } else {
            texturePath = "assets/tile-brown.png";
        }
        break;
    }

    mSprite->SetTexture(GetGame()->GetTexture(texturePath));
}
