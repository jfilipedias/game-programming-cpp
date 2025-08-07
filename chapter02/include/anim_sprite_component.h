#pragma once
#include "sprite_component.h"
#include <vector>

class AnimSpriteComponent : public SpriteComponent {
public:
    AnimSpriteComponent(class Actor* owner, int drawOrder = 150);

    void Update(float deltaTimer) override;
    void SetAnimTextures(const std::vector<SDL_Texture*>& textures);

    float GetAnimFPS() const { return mAnimFPS; }
    void SetAnimFPS(float fps) { mAnimFPS = fps; }

private:
    std::vector<SDL_Texture*> mAnimTextures;
    float mCurrFrame;
    float mAnimFPS;
};
