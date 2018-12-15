#include "GunItem.h"

GunItem::GunItem(const LoaderParams& pParams) : GameObject(pParams)
{
    destoryTime = SDL_GetTicks() + 6500u;
}

void GunItem::Update()
{
    if (SDL_GetTicks() > destoryTime)
    {
        Destroy();
    }
}

void GunItem::Draw()
{
    GameObject::Draw();
}