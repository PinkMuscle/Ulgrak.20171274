#include "UIBox.h"
#include "TextureManager.h"

UIBox::UIBox(const LoaderParams& pParams) : GameObject(pParams)
{
    frames = 0;
    frameSpeed = 1000;
}

UIBox::UIBox(const LoaderParams& pParams, int frameSpeed, int frames) : GameObject(pParams)
{
    this->frameSpeed = frameSpeed;
    this->frames = frames;
}

void UIBox::Draw()
{
    TextureManager::Instance()->DrawFrame(textureID, int(position.x), int(position.y), width, height, currentRow, currentFrame, scale, SDL_FLIP_NONE);
}

void UIBox::Update()
{
    if (frames != 0)
    {
        currentFrame = int(((SDL_GetTicks() / frameSpeed) % frames));
    }
}