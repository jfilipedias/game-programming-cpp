#pragma once
#include "actor.h"

class Grid : public Actor {
public:
    Grid(class Game* game);

    void UpdateActor(float deltaTime) override;
    void ProcessClick(int x, int y);
    bool FindPath(class Tile* start, class Tile* goal);
    void BuildTower();

    class Tile* GetStartTile();
    class Tile* GetEndTile();

private:
    void SelectTile(size_t row, size_t col);
    void UpdatePathTiles(class Tile* start);

    class Tile* mSelectedTile;

    std::vector<std::vector<class Tile*>> mTiles;

    float mNextEnemy;

    const size_t mNumRows{ 7 };
    const size_t mNumCols{ 16 };
    const float mStartY{ 192.0f };
    const float mTileSize{ 64.0f };
    const float mEnemyTime{ 1.5f };
};
