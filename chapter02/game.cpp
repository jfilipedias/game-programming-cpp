#include "game.h"
#include "actor.h"
#include "sprite_component.h"
#include <algorithm>

Game::Game()
    : mWindow(nullptr),
      mRenderer(nullptr),
      mTicksCount(0),
      mIsRunning(true),
      mUpdatingActors(false) {}

bool Game::Initialize() {
    bool success = SDL_Init(SDL_INIT_VIDEO);
    if (!success) {
        SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
        return false;
    }

    mWindow = SDL_CreateWindow("Game Programming in C++ (Chapter 2)", 1024, 768, 0);
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

    LoadData();

    mTicksCount = SDL_GetTicks();

    return true;
}

void Game::RunLoop() {
    while (mIsRunning) {
        ProcessInput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown() {
    while (!mActors.empty()) {
        delete mActors.back();
    }

    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT:
            mIsRunning = false;
            break;
        }
    }

    const bool* state = SDL_GetKeyboardState(nullptr);
    if (state[SDL_SCANCODE_ESCAPE]) {
        mIsRunning = false;
    }
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

    for (Actor* pendding : mPenddingActors) {
        mActors.emplace_back(pendding);
    }
    mPenddingActors.clear();

    std::vector<Actor*> deadActors;
    for (Actor* actor : mActors) {
        if (actor->GetState() == Actor::EDead) {
            deadActors.emplace_back(actor);
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

void Game::LoadData() {}

void Game::AddActor(Actor* actor) {
    if (mUpdatingActors) {
        mPenddingActors.emplace_back(actor);
    } else {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor* actor) {
    std::vector<Actor*>::iterator iter = std::find(mPenddingActors.begin(), mPenddingActors.end(), actor);
    if (iter != mPenddingActors.end()) {
        std::iter_swap(iter, mPenddingActors.end());
        mPenddingActors.pop_back();
    }

    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end()) {
        std::iter_swap(iter, mActors.end());
        mActors.pop_back();
    }
}

void Game::AddSprite(SpriteComponent* sprite) {
    int drawOrder = sprite->GetDrawOrder();
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
    std::vector<SpriteComponent*>::const_iterator iter = std::find(mSprites.begin(), mSprites.end(), sprite);
    mSprites.erase(iter);
}
