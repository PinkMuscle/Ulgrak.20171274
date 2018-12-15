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
        flip = SDL_FLIP_NONE;
    }
    else if (velocity.x < 0)
    {
        flip = SDL_FLIP_HORIZONTAL;
    }
    //TextureManager::Instance()->DrawFrame(textureID, int(position.x - Camera::Instance()->GetX() + 0.5f), int(position.x + 0.5f), width, height, currentRow, currentFrame, scale, flip);
    TextureManager::Instance()->DrawFrame(textureID, Camera::Instance()->GetXOnCamera(position.x), Camera::Instance()->GetYOnCamera(position.y), width, height, currentRow, currentFrame, scale * Camera::Instance()->GetScale(), flip);
}

void GameObject::Update()
{
    position += velocity;
}

void GameObject::Clean()
{
}