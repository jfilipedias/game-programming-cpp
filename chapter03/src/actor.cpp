#include "actor.h"
#include "component.h"
#include "game.h"
#include <algorithm>

Actor::Actor(Game* game)
    : mState{ EActive },
      mPosition{ Vector2::Zero },
      mScale{ 1.0f },
      mRotation{ 0.0f },
      mGame{ game } {
    mGame->AddActor(this);
}

Actor::~Actor() {
    mGame->RemoveActor(this);
    while (!mComponents.empty()) {
        delete mComponents.back();
    }
}

void Actor::Update(float deltaTime) {
    if (mState == Actor::EActive || mState == Actor::ERespawning) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) {
    for (Component* comp : mComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {}

void Actor::ProcessInput(const bool* keyState) {
    if (mState != EActive) {
        return;
    }

    for (Component* comp : mComponents) {
        comp->ProcessInput(keyState);
    }

    ActorInput(keyState);
}

void Actor::ActorInput(const bool* keyState) {}

void Actor::AddComponent(Component* component) {
    int order{ component->GetUpdateOrder() };
    std::vector<Component*>::const_iterator iter;
    for (iter = mComponents.begin(); iter != mComponents.end(); ++iter) {
        if (order < (*iter)->GetUpdateOrder()) {
            break;
        }
    }

    mComponents.insert(iter, component);
}

void Actor::RemoveComponent(Component* component) {
    std::vector<Component*>::iterator iter{ std::ranges::find(mComponents, component) };
    if (iter != mComponents.end()) {
        mComponents.erase(iter);
    }
}
