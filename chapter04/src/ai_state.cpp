#include "ai_state.h"
#include "ai_component.h"
#include <SDL3/SDL.h>

void PatrolState::Update(float deltaTime) {
    SDL_Log("Update %s state", GetName());

    bool dead{ true };
    if (dead) {
        mOwner->ChangeState("Death");
    }
}
void PatrolState::OnEnter() {
    SDL_Log("Entering %s state", GetName());
}

void PatrolState::OnExit() {
    SDL_Log("Exiting %s state", GetName());
}

void AttackState::Update(float deltaTime) {
    SDL_Log("Updating %s state", GetName());
}

void AttackState::OnEnter() {
    SDL_Log("Entering %s state", GetName());
}

void AttackState::OnExit() {
    SDL_Log("Exiting %s state", GetName());
}

void DeathState::Update(float deltaTime) {
    SDL_Log("Updating %s state", GetName());
}

void DeathState::OnEnter() {
    SDL_Log("Entering %s state", GetName());
}

void DeathState::OnExit() {
    SDL_Log("Exiting %s state", GetName());
}
