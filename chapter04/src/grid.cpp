#include "grid.h"
#include "tile.h"

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
    GetGoalTile()->SetTileState(Tile::EBase);

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

void Grid::ProcessClick(int x, int y) {
    y -= static_cast<int>(mStartY - mTileSize / 2);
    if (y < 0) {
        return;
    }

    x /= static_cast<int>(mTileSize);
    y /= static_cast<int>(mTileSize);
    if (x >= 0 && x < static_cast<int>(mNumCols) && y >= 0 && y < static_cast<int>(mNumRows)) {
        SelectTile(x, y);
    }
}
