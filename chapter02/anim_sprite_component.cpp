#include "anim_sprite_component.h"
#include "actor.h"

AnimSpriteComponent::AnimSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent{ owner, drawOrder },
      mCurrFrame{ 0 },
      mAnimFPS{ 24.0f } {}

void AnimSpriteComponent::SetAnimTextures(std::vector<SDL_Texture*>& textures) {
    mAnimTextures = textures;
    if (mAnimTextures.size() > 0) {
        mCurrFrame = 0;
        SetTexture(mAnimTextures[0]);
    }
}

void AnimSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);

    if (mAnimTextures.size() > 0) {
        mCurrFrame += mAnimFPS * deltaTime;
        while (mCurrFrame >= mAnimTextures.size()) {
            mCurrFrame -= mAnimTextures.size();
        }

        SetTexture(mAnimTextures[static_cast<int>(mCurrFrame)]);
    }
}
