#include "Bullet.h"

constexpr float defaultSpeed = 6.0f;

Bullet::Bullet(const LoaderParams& pParams, SDL_RendererFlip flip, float damage_) : GameObject(pParams), damage(damage_)
{
    destoryTime = SDL_GetTicks() + 3000u;
    if (flip == SDL_FLIP_NONE)
    {
        velocity.x = defaultSpeed;
    }
    else
    {
        velocity.x = -defaultSpeed;
    }
}

Bullet::Bullet(const LoaderParams& pParams, SDL_RendererFlip flip, float damage_, float speed_) : GameObject(pParams), damage(damage_)
{
    destoryTime = SDL_GetTicks() + 5000u;
    if (flip == SDL_FLIP_NONE)
    {
        velocity.x = speed_;
    }
    else
    {
        velocity.x = -speed_;
    }
}

void Bullet::Update()
{
    if (SDL_GetTicks() > destoryTime)
    {
        Destroy();
    }
    GameObject::Update();
}

void Bullet::Draw()
{
    GameObject::Draw();
}