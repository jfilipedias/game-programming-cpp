#pragma once
#include "actor.h"

class Tile : public Actor {
public:
    friend class Grid;
    enum TileState {
        EDefault,
        EPath,
        EStart,
        EBase,
    };

    Tile(class Game* game);

    void SetTileState(TileState state);
    TileState GetTileState() const { return mTileState; }
    void ToggleSelect();
    const Tile* GetParent() const { return mParent; }

private:
    Tile* mParent;
    std::vector<Tile*> mAdjacents;
    float f;
    float g;
    float h;
    bool mInOpenSet;
    bool mInClosedSet;
    bool mBlocked;

    bool mSelected;
    TileState mTileState;
    class SpriteComponent* mSprite;
    void UpdateTexture();
};