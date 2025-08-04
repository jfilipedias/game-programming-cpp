#include "sprite_component.h"
#include "actor.h"
#include "game.h"
#include "math.h"

SpriteComponent::SpriteComponent(Actor* owner, int drawOrder)
    : Component{ owner },
      mTexture{ nullptr },
      mDrawOrder{ drawOrder },
      mTexWidth{ 0 },
      mTexHeight{ 0 } {
    mOwner->GetGame()->AddSprite(this);
}

SpriteComponent::~SpriteComponent() {
    mOwner->GetGame()->RemoveSprite(this);
}

void SpriteComponent::Draw(SDL_Renderer* renderer) {
    if (mTexture == nullptr) {
        return;
    }

    SDL_FRect rect;
    rect.w = mTexWidth * mOwner->GetScale();
    rect.h = mTexHeight * mOwner->GetScale();
    rect.x = mOwner->GetPosition().x - rect.w / 2;
    rect.y = mOwner->GetPosition().y - rect.h / 2;

    SDL_RenderTextureRotated(
        renderer,
        mTexture,
        nullptr,
        &rect,
        -Math::ToDegrees(mOwner->GetRotation()),
        nullptr,
        SDL_FLIP_NONE);
}

void SpriteComponent::SetTexture(SDL_Texture* texture) {
    mTexture = texture;
    SDL_GetTextureSize(texture, &mTexWidth, &mTexHeight);
}
