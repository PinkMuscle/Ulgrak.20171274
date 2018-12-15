#include "Background.h"

Background::Background(const LoaderParams& pParams) : GameObject(pParams)
{
}

void Background::Draw()
{
    GameObject::Draw();
}

void Background::Update()
{
    currentFrame = int(((SDL_GetTicks() / 1000) % 2));
}

void Background::Clean()
{
    GameObject::Clean();
}