#pragma once
#include "game_math.h"
#include <SDL3/SDL.h>
#include <string>
#include <unordered_map>
#include <vector>

class Game {
public:
    Game();
    bool Initialize();
    void RunLoop();
    void Shutdown();

    void AddActor(class Actor* actor);
    void RemoveActor(class Actor* actor);

    void AddSprite(class SpriteComponent* sprite);
    void RemoveSprite(class SpriteComponent* sprite);

    SDL_Texture* GetTexture(const std::string& fileName);

    class Grid* GetGrid() { return mGrid; }
    std::vector<class Enemy*> GetEnemies() { return mEnemies; }
    class Enemy* GetNearestEnemy(const Vector2& pos);

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput();
    void LoadData();
    void UnloadData();

    std::unordered_map<std::string, SDL_Texture*> mTextures;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPendingActors;

    std::vector<class SpriteComponent*> mSprites;

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint32 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;

    class Grid* mGrid;
    std::vector<class Enemy*> mEnemies;
    float mNextEnemy;
};