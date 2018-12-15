#include "GunGenerator.h"
#include "GunItem.h"

GunGenerator::GunGenerator(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& items_) : GameObject(pParams), items(items_)
{
    destoryTime = SDL_GetTicks() + 1500u;
}

void GunGenerator::Update()
{
    currentFrame = int(((SDL_GetTicks() / 200) % 2));
    if (SDL_GetTicks() > destoryTime)
    {
        Destroy();
    }
}

void GunGenerator::Draw()
{
    GameObject::Draw();
}