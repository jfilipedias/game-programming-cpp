#pragma once
#include "game_math.h"
#include <vector>

class Actor {
public:
    enum State {
        EActive,
        EPaused,
        EDead
    };

    Actor(class Game* game);
    virtual ~Actor();

    void Update(float deltaTime);
    void UpdateComponents(float deltaTime) const;
    virtual void UpdateActor(float deltaTime);

    void AddComponent(class Component* component);
    void RemoveComponent(const class Component* component);

    const Vector2& GetPosition() const { return mPosition; }
    void SetPosition(const Vector2& pos) { mPosition = pos; }
    float GetScale() { return mScale; }
    void SetScale(float scale) { mScale = scale; }
    float GetRotation() { return mRotation; }
    void SetRotation(float rotation) { mRotation = rotation; }

    State GetState() const { return mState; }
    void SetState(State state) { mState = state; }

    class Game* GetGame() { return mGame; }

private:
    State mState;
    Vector2 mPosition;
    float mScale;
    float mRotation;
    std::vector<class Component*> mComponents;
    class Game* mGame;
};
