#include "bg_sprite_component.h"
#include "actor.h"

BGSpriteComponent::BGSpriteComponent(Actor* owner, int drawOrder)
    : SpriteComponent{ owner, drawOrder },
      mScrollSpeed{ 0.0f } {}

void BGSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    for (BGTexture& bgTex : mBGTextures) {
        bgTex.mOffset.x += mScrollSpeed * deltaTime;

        if (bgTex.mOffset.x < -mScreenSize.x) {
            // Reset offset to the right of the last bg texture
            bgTex.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
        }
    }
}

void BGSpriteComponent::Draw(SDL_Renderer* renderer) {
    for (BGTexture& bgTex : mBGTextures) {
        SDL_FRect rect;
        rect.w = mScreenSize.x;
        rect.h = mScreenSize.y;
        rect.x = mOwner->GetPosition().x - mScreenSize.x / 2 + bgTex.mOffset.x;
        rect.y = mOwner->GetPosition().y - mScreenSize.y / 2 + bgTex.mOffset.y;

        SDL_RenderTexture(renderer, bgTex.mTexture, nullptr, &rect);
    }
}

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures) {
    int count{ 0 };
    for (SDL_Texture* tex : textures) {
        BGTexture bgTexture{ tex, Vector2{ count * mScreenSize.x, 0 } };
        mBGTextures.emplace_back(bgTexture);
        count++;
    }
}