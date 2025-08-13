#pragma once

class AIState {
public:
    AIState(class AIComponent* owner)
        : mOwner{ owner } {}

    virtual void Update(float deltaTime) = 0;
    virtual void OnEnter() = 0;
    virtual void OnExit() = 0;

    virtual const char* GetName() const = 0;

protected:
    class AIComponent* mOwner;
};

class DeathPatrol : AIState {
public:
    DeathPatrol(class AIComponent* owner)
        : AIState{ owner } {}

    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    const char* GetName() const override {
        return "Patrol";
    }
};

class DeathAttack : AIState {
public:
    DeathAttack(class AIComponent* owner)
        : AIState{ owner } {}

    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    const char* GetName() const override {
        return "Attack";
    }
};

class DeathState : AIState {
public:
    DeathState(class AIComponent* owner)
        : AIState{ owner } {}

    void Update(float deltaTime) override;
    void OnEnter() override;
    void OnExit() override;

    const char* GetName() const override {
        return "Death";
    }
};
