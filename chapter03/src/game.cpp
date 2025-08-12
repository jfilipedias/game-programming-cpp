#include "game.h"
#include "actor.h"
#include "asteroid.h"
#include "bg_sprite_component.h"
#include "game_math.h"
#include "game_random.h"
#include "ship.h"
#include "sprite_component.h"
#include <SDL3_image/SDL_image.h>
#include <algorithm>

Game::Game()
    : mWindow{ nullptr },
      mRenderer{ nullptr },
      mTicksCount{ 0 },
      mIsRunning{ true },
      mUpdatingActors{ false },
      mShip(nullptr) {}

bool Game::Initialize() {
    bool success{ SDL_Init(SDL_INIT_VIDEO) };
    if (!success) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 3)", 1024, 768, 0);
    if (!mWindow) {
        SDL_Log("Failed to create window: %s", SDL_GetError());
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, nullptr);
    if (!mRenderer) {
        SDL_Log("Failed to create renderer: %s", SDL_GetError());
        return false;
    }

    if (!SDL_SetRenderVSync(mRenderer, 1)) {
        SDL_Log("Failed to enable VSync: %s", SDL_GetError());
        return false;
    }

    GameRandom::Init();

    LoadData();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::Shutdown() {
    UnloadData();
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::LoadData() {
    mShip = new Ship{ this };
    mShip->SetPosition(Vector2{ 512.0f, 384.0f });
    mShip->SetRotation(GameMath::PiOver2);

    Actor* bgActor = new Actor(this);
    bgActor->SetPosition(Vector2{ 512.0f, 384.0f });

    std::vector<SDL_Texture*> bgTex{ GetTexture("assets/background.png") };

    BGSpriteComponent* bgComp = new BGSpriteComponent{ bgActor };
    bgComp->SetScreenSize(Vector2{ 1024.0f, 768.0f });
    bgComp->SetScrollSpeed(0.0f);
    bgComp->SetBGTextures(bgTex);

    const int numAsteroids{ 20 };
    for (int i{ 0 }; i < numAsteroids; i++) {
        new Asteroid{ this };
    }
}

void Game::UnloadData() {
    while (!mActors.empty()) {
        delete mActors.back();
    }

    for (std::pair<std::string, SDL_Texture*> pair : mTextures) {
        SDL_DestroyTexture(pair.second);
    }
    mTextures.clear();
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            mIsRunning = false;
            break;
        default:;
        }
    }

    const bool* state{ SDL_GetKeyboardState(nullptr) };
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }

    mUpdatingActors = true;
    for (Actor* actor : mActors) {
        actor->ProcessInput(state);
    }
    mUpdatingActors = false;
}

void Game::UpdateGame() {
    Uint64 deadline = SDL_GetTicks() + 16;
    while (deadline > SDL_GetTicks())
        ;

    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    if (deltaTime > 0.05f) {
        deltaTime = 0.05f;
    }
    mTicksCount = SDL_GetTicks();

    mUpdatingActors = true;
    for (Actor* actor : mActors) {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;

    for (Actor* pendding : mPendingActors) {
        mActors.push_back(pendding);
    }
    mPendingActors.clear();

    std::vector<Actor*> deadActors;
    for (Actor* actor : mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.push_back(actor);
        }
    }

    for (Actor* actor : deadActors) {
        delete actor;
    }
}

void Game::GenerateOutput() {
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
    SDL_RenderClear(mRenderer);

    for (SpriteComponent* sprite : mSprites) {
        sprite->Draw(mRenderer);
    }

    SDL_RenderPresent(mRenderer);
}

void Game::AddActor(Actor* actor) {
    if (mUpdatingActors) {
        mPendingActors.push_back(actor);
    } else {
        mActors.push_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    std::vector<Actor*>::iterator iter{ std::ranges::find(mPendingActors, actor) };
    if (iter != mPendingActors.end()) {
        std::iter_swap(iter, mPendingActors.end());
        mPendingActors.pop_back();
    }

    iter = std::ranges::find(mActors, actor);
    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end());
        mActors.pop_back();
    }
}

void Game::AddAsteroid(Asteroid* ast) {
    mAsteroids.push_back(ast);
}

void Game::RemoveAsteroid(Asteroid* ast) {
    std::vector<Asteroid*>::iterator iter{ std::ranges::find(mAsteroids, ast) };
    if (iter != mAsteroids.end()) {
        mAsteroids.erase(iter);
    }
}

void Game::AddSprite(SpriteComponent* sprite) {
    int drawOrder{ sprite->GetDrawOrder() };
    std::vector<SpriteComponent*>::const_iterator iter;
    for (iter = mSprites.begin(); iter != mSprites.end(); ++iter) {
        if (drawOrder < (*iter)->GetDrawOrder()) {
            break;
        }
    }

    mSprites.insert(iter, sprite);
}

void Game::RemoveSprite(SpriteComponent* sprite) {
    // Can't swap because it ruins ordering
    std::vector<SpriteComponent*>::const_iterator iter{ std::ranges::find(mSprites, sprite) };
    mSprites.erase(iter);
}

SDL_Texture* Game::GetTexture(const std::string& fileName) {
    std::unordered_map<std::string, SDL_Texture*>::iterator iter{ mTextures.find(fileName.c_str()) };
    if (iter != mTextures.end()) {
        return iter->second;
    }

    SDL_Surface* surf{ IMG_Load(fileName.c_str()) };
    if (!surf) {
        SDL_Log("Failed to load texture file %s", fileName.c_str());
        return nullptr;
    }

    SDL_Texture* tex{ SDL_CreateTextureFromSurface(mRenderer, surf) };
    SDL_DestroySurface(surf);

    if (!tex) {
        SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
        return nullptr;
    }

    mTextures.emplace(fileName.c_str(), tex);
    return tex;
}
