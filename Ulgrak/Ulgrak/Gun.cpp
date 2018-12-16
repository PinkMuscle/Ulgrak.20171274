#include "Gun.h"
#include "Bullet.h"

Gun::Gun(const LoaderParams& pParams, GameObject& player_, std::vector<std::unique_ptr<GameObject>>& projectiles_)
    : GameObject(pParams), player(player_), projectiles(projectiles_)
{
    Change("G0");
}

void Gun::Update()
{
    flip = player.GetFlip();
    if (flip == SDL_FLIP_NONE)
    {
        position = player.GetPosition() + Vector2D(27, 12);
    }
    else
    {
        position = player.GetPosition() + Vector2D(5.0f - width, 12);
    }
}

void Gun::Draw()
{
    GameObject::Draw();
}

void Gun::Change(std::string tag)
{
    this->tag = tag;

    if (tag == "G0")
    {
        textureID = "gun0";
        width = 10;
        height = 11;
        magazine = -1;
        damage = 10;
        fireRate = 300;
    }
    else if (tag == "G1")
    {
        textureID = "gun1";
        width = 19;
        height = 11;
        magazine = 6;
        damage = 20;
        fireRate = 600;
    }

    nextFire = SDL_GetTicks() + fireRate;
}

void Gun::Shot()
{
    if (SDL_GetTicks() > nextFire)
    {
        if (tag == "G0")
        {
            projectiles.emplace_back(std::make_unique<Bullet>(LoaderParams(int(position.x), int(position.y) + 4, 4, 1, 2, "bullet", player.GetTag()), flip, damage));
        }
        else if (tag == "G1")
        {
            projectiles.emplace_back(std::make_unique<Bullet>(LoaderParams(int(position.x), int(position.y) + 4, 4, 1, 3, "bullet_purple", player.GetTag()), flip, damage));
        }
        nextFire = SDL_GetTicks() + fireRate;

        if (magazine != -1)
        {
            magazine--;
            if (magazine == 0)
            {
                Change("G0");
            }
        }
    }
}