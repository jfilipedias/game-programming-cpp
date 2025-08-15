#include "ai_component.h"
#include "actor.h"
#include "ai_state.h"
#include <SDL3/SDL.h>

AIComponent::AIComponent(Actor* owner)
    : Component{ owner } {}

void AIComponent::RegisterState(const AIState* state) {
    mStateMap.emplace(state->GetName(), state);
}

void AIComponent::Update(float deltaTime) {
    if (mCurrentState) {
        mCurrentState->Update(deltaTime);
    }
}

void AIComponent::ChangeState(const std::string& name) {
    if (mCurrentState) {
        mCurrentState->OnExit();
    }

    std::unordered_map<std::string, AIState*>::iterator iter{ mStateMap.find(name) };
    if (iter != mStateMap.end()) {
        mCurrentState = iter->second;
        mCurrentState->OnEnter();
    } else {
        SDL_Log("Could not find the AIState %s in the state map", name.c_str());
        mCurrentState = nullptr;
    }
}
