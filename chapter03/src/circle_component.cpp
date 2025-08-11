#include "circle_component.h"
#include "actor.h"

CircleComponent::CircleComponent(Actor* owner)
    : Component{ owner } {}

float CircleComponent::GetRadius() const {
    return mOwner->GetScale() * mRadius;
}

const Vector2& CircleComponent::GetCenter() const {
    return mOwner->GetPosition();
}

bool Intersect(const CircleComponent& a, const CircleComponent& b) {
    Vector2 diff{ a.GetCenter() - b.GetCenter() };
    float distSq{ diff.LengthSquared() };

    float radiiSq{ a.GetRadius() + b.GetRadius() };
    radiiSq *= radiiSq;

    return distSq <= radiiSq;
}
