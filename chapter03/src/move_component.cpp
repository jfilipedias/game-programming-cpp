#include "move_component.h"
#include "actor.h"
#include "game_math.h"

void MoveComponent::Update(float deltaTime) {
    if (!GameMath::NearZero(mAngularSpeed)) {
        float rot{ mOwner->GetRotation() };
        rot += mAngularSpeed * deltaTime;
        mOwner->SetRotation(rot);
    }

    if (!GameMath::NearZero(mForwardSpeed)) {
        Vector2 pos{ mOwner->GetPosition() };
        pos += mOwner->GetForward() * mForwardSpeed * deltaTime;

        // (Screen wrapping code only for asteroids)
        if (pos.x < 0.0f) {
            pos.x = 1022.0f;
        } else if (pos.x > 1024.0f) {
            pos.x = 2.0f;
        }

        if (pos.y < 0.0f) {
            pos.y = 766.0f;
        } else if (pos.y > 768.0f) {
            pos.y = 2.0f;
        }

        mOwner->SetPosition(pos);
    }
}
