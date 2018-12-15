#include "GameObject.h"
#include "TextureManager.h"
#include "Camera.h"

GameObject::GameObject(const LoaderParams& pParams) : position(float(pParams.GetX()), float(pParams.GetY()))
{
    width = pParams.GetWidth();
    height = pParams.GetHeight();
    textureID = pParams.GetTextureID();
    scale = pParams.GetScale();
    currentRow = 0;
    currentFrame = 0;
}

void GameObject::Draw()
{
    if (velocity.x > 0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    else if (velocity.x < 0)
    {
        flip = SDL_FLIP_NONE;
    }
    TextureManager::Instance()->DrawFrame(textureID, int(position.x - Camera::Instance()->GetX() + 0.5f), int(position.x + 0.5f), width, height, currentRow, currentFrame, scale, flip);
}

void GameObject::Update()
{
    velocity += acceleration;
    position += velocity;
}

void GameObject::Clean()
{
}