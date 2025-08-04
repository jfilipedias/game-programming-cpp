#include "bg_sprite_component.h"

void BGSpriteComponent::SetBGTextures(const std::vector<SDL_Texture*>& textures) {
    int count{ 0 };
    for (SDL_Texture* tex : textures) {
        BGTexture bgTexture{ tex, Vector2{ count * mScreenSize.x, 0 } };
        mBGTextures.emplace_back(bgTexture);
        count++;
    }
}

void BGSpriteComponent::Update(float deltaTime) {
    SpriteComponent::Update(deltaTime);
    for (BGTexture& bgTex : mBGTextures) {
        bgTex.mOffset.x += mScreenSpeed * deltaTime;

        bool isOffScreen{ bgTex.mOffset.x < -mScreenSize.x };
        if (isOffScreen) {
            // Reset offset to the right of the last bg texture
            bgTex.mOffset.x = (mBGTextures.size() - 1) * mScreenSize.x - 1;
        }
    }
}