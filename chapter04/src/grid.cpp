#include "grid.h"
#include "enemy.h"
#include "tile.h"
#include "tower.h"

Grid::Grid(class Game* game)
    : Actor{ game },
      mSelectedTile{ nullptr } {
    mTiles.resize(mNumRows);

    for (size_t i{ 0 }; i < mTiles.size(); i++) {
        mTiles[i].resize(mNumCols);
    }

    for (size_t i{ 0 }; i < mNumRows; i++) {
        for (size_t j{ 0 }; j < mNumCols; j++) {
            mTiles[i][j] = new Tile{ GetGame() };
            mTiles[i][j]->SetPosition(Vector2{
                mTileSize / 2.0f + j * mTileSize,
                mStartY + i * mTileSize });
        }
    }

    GetStartTile()->SetTileState(Tile::EStart);
    GetEndTile()->SetTileState(Tile::EBase);

    for (size_t i{ 0 }; i < mNumRows; i++) {
        for (size_t j{ 0 }; j < mNumCols; j++) {
            if (i > 0) {
                mTiles[i][j]->mAdjacents.push_back(mTiles[i - 1][j]);
            }

            if (i < mNumRows - 1) {
                mTiles[i][j]->mAdjacents.push_back(mTiles[i + 1][j]);
            }

            if (j > 0) {
                mTiles[i][j]->mAdjacents.push_back(mTiles[i][j - 1]);
            }

            if (j < mNumCols - 1) {
                mTiles[i][j]->mAdjacents.push_back(mTiles[i][j + 1]);
            }
        }
    }

    FindPath(GetEndTile(), GetStartTile());
    UpdatePathTiles(GetStartTile());

    mNextEnemy = mEnemyTime;
}

void Grid::SelectTile(size_t row, size_t col) {
    Tile::TileState tileState{
        mTiles[row][col]->GetTileState()
    };

    if (tileState != Tile::EStart && tileState != Tile::EBase) {
        if (mSelectedTile) {
            mSelectedTile->ToggleSelect();
        }

        mSelectedTile = mTiles[row][col];
        mSelectedTile->ToggleSelect();
    }
}

void Grid::UpdatePathTiles(Tile* start) {
    for (size_t i{ 0 }; i < mNumRows; i++) {
        for (size_t j{ 0 }; j < mNumCols; j++) {
            mTiles[i][j]->SetTileState(Tile::EDefault);
        }
    }

    Tile* t{ start->mParent };
    while (t != GetEndTile()) {
        t->SetTileState(Tile::EPath);
        t = t->mParent;
    }
}

void Grid::ProcessClick(int x, int y) {
    y -= static_cast<int>(mStartY - mTileSize / 2);
    if (y < 0) {
        return;
    }

    x /= static_cast<int>(mTileSize);
    y /= static_cast<int>(mTileSize);
    if (x >= 0 && x < static_cast<int>(mNumCols) && y >= 0 && y < static_cast<int>(mNumRows)) {
        SelectTile(y, x);
    }
}

// A* pathfinding algorithm
bool Grid::FindPath(Tile* start, Tile* goal) {
    for (size_t i{ 0 }; i < mNumRows; i++) {
        for (size_t j{ 0 }; j < mNumCols; j++) {
            mTiles[i][j]->g = 0.0f;
            mTiles[i][j]->mInOpenSet = false;
            mTiles[i][j]->mInClosedSet = false;
        }
    }

    std::vector<Tile*> openSet;

    Tile* current = start;
    current->mInOpenSet = true;

    while (current != goal) {
        for (Tile* neighbor : current->mAdjacents) {
            if (neighbor->mBlocked || neighbor->mInClosedSet) {
                continue;
            }

            if (neighbor->mInOpenSet) {
                float newG = current->g + mTileSize;
                if (newG < neighbor->g) {
                    neighbor->mParent = current;
                    neighbor->g = newG;
                    neighbor->f = neighbor->g + neighbor->h;
                }
            } else {
                neighbor->mParent = current;
                neighbor->h = (neighbor->GetPosition() - goal->GetPosition()).Length();
                neighbor->g = neighbor->g + mTileSize;
                neighbor->f = neighbor->g + neighbor->h;
                openSet.push_back(neighbor);
                neighbor->mInOpenSet = true;
            }
        }

        if (openSet.empty()) {
            break;
        }

        std::vector<Tile*>::iterator iter{
            std::min_element(
                openSet.begin(),
                openSet.end(),
                [](Tile* a, Tile* b) {
                    return a->f < b->f;
                })
        };

        current = *iter;
        openSet.erase(iter);
        current->mInOpenSet = false;
        current->mInClosedSet = true;
    }

    return current == goal;
}

void Grid::BuildTower() {
    if (mSelectedTile == nullptr || mSelectedTile->mBlocked) {
        return;
    }

    mSelectedTile->mBlocked = true;
    if (FindPath(GetEndTile(), GetStartTile())) {
        Tower* t = new Tower{ GetGame() };
        t->SetPosition(mSelectedTile->GetPosition());
    } else {
        mSelectedTile->mBlocked = false;
        FindPath(GetEndTile(), GetStartTile());
    }

    UpdatePathTiles(GetStartTile());
}

Tile* Grid::GetStartTile() {
    return mTiles[3][0];
}

Tile* Grid::GetEndTile() {
    return mTiles[3][15];
}

void Grid::UpdateActor(float deltaTime) {
    Actor::UpdateActor(deltaTime);

    mNextEnemy -= deltaTime;
    if (mNextEnemy <= 0.0f) {
        new Enemy{ GetGame() };
        mNextEnemy += mEnemyTime;
    }
}
