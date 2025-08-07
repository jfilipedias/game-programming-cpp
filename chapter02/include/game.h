#pragma once
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

private:
    void ProcessInput();
    void UpdateGame();
    void GenerateOutput() const;
    void LoadData();
    void UnloadData();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;
    Uint64 mTicksCount;
    bool mIsRunning;
    bool mUpdatingActors;

    class Ship* mShip;

    std::vector<class Actor*> mActors;
    std::vector<class Actor*> mPenddingActors;
    std::vector<class SpriteComponent*> mSprites;

    std::unordered_map<std::string, SDL_Texture*> mTextures;
};
