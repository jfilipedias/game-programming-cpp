#include "actor.h"
#include "component.h"
#include "game.h"
#include "game_math.h"

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
    if (mState == State::EActive) {
        UpdateComponents(deltaTime);
        UpdateActor(deltaTime);
    }
}

void Actor::UpdateComponents(float deltaTime) const {
    for (Component* comp : mComponents) {
        comp->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime) {}

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

void Actor::RemoveComponent(const Component* component) {
    std::vector<Component*>::iterator iter{ std::ranges::find(mComponents, component) };
    if (iter != mComponents.end()) {
        mComponents.erase(iter);
    }
}
