#include "Explosion.h"

Explosion::Explosion(const LoaderParams& pParams) : GameObject(pParams), frameSpeed(50u)
{
    nextFrameTime = SDL_GetTicks() + frameSpeed;
}

void Explosion::Draw()
{
    GameObject::Draw();
}

void Explosion::Update()
{
    if (SDL_GetTicks() > nextFrameTime)
    {
        nextFrameTime = SDL_GetTicks() + frameSpeed;
        currentFrame++;
        if (currentFrame > 4)
        {
            currentFrame = 0;
            currentRow++;
            if (currentRow > 5)
            {
                Destroy();
            }
        }
    }
}

void Explosion::Clean()
{
    GameObject::Clean();
}