#include "input_component.h"

InputComponent::InputComponent(Actor* owner)
    : MoveComponent{ owner } {}

void InputComponent::ProcessInput(const bool* keyState) {
    float forwardSpeed{ 0.0f };
    if (keyState[mForwardKey]) {
        forwardSpeed += mMaxForwardSpeed;
    }

    if (keyState[mBackKey]) {
        forwardSpeed -= mMaxForwardSpeed;
    }

    SetForwardSpeed(forwardSpeed);

    float angularSpeed{ 0.0f };
    if (keyState[mClockwiseKey]) {
        angularSpeed += mMaxAngularSpeed;
    }

    if (keyState[mCounterClockwiseKey]) {
        angularSpeed -= mMaxAngularSpeed;
    }

    SetAngularSpeed(angularSpeed);
}
