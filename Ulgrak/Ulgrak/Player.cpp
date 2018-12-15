#include "Player.h"
#include "InputHandler.h"
#include "Collision.h"
#include <iostream>

constexpr float firstJumpPower = -3.0f;
constexpr float secondJumpPower = -3.6f;
constexpr float gravity = 0.07f;

Player::Player(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& platforms_, int id) : GameObject(pParams), platforms(platforms_)
{
    playerID = id;
}

void Player::Draw()
{
    GameObject::Draw();
}

void Player::Update()
{
    currentFrame = int(((SDL_GetTicks() / 100) % 2));

    if (onPlatform)
    {
        position.y += 1;

        onPlatform = [&]() ->bool
        {
            for (auto& platform : platforms)
            {
                if (Collision::AABB(this, platform.get()))
                {
                    return true;
                }
            }
            jump = 1;
            return false;
        }();

        position.y -= 1;
    }


    HandleInput();
    if (!onPlatform)
    {
        velocity.y += gravity;
    }


    //포지션 변경하면서 충돌 체크
    position.x += velocity.x;
    for (auto& platform : platforms)
    {
        if (Collision::AABB(this, platform.get()))
        {
            if (velocity.x > 0)
            {
                position.x = platform->GetPosition().x - width * scale;
            }
            else
            {
                position.x = platform->GetPosition().x + platform->GetWidth() * platform->GetScale();
            }
            velocity.x = 0;
        }
    }

    position.y += velocity.y;
    for (auto& platform : platforms)
    {
        if (Collision::AABB(this, platform.get()))
        {
            if (velocity.y > 0)
            {
                position.y = platform->GetPosition().y - height * scale;
                onPlatform = true;
                jump = 2;
            }
            else
            {
                position.y = platform->GetPosition().y + platform->GetHeight() * platform->GetScale();
            }
            velocity.y = 0;
        }
    }
}

void Player::Clean()
{
    GameObject::Clean();
}

void Player::HandleInput()
{
    float direction = 0.0f;

    if (playerID == 0)
    {
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D))
        {
            direction = 1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A))
        {
            direction = -1.0f;
        }

        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_W))
        {
            if (!prevButtonState)
            {
                prevButtonState = true;
                if (jump > 0)
                {
                    if (jump == 2) velocity.y = firstJumpPower;
                    else velocity.y = secondJumpPower;
                    onPlatform = false;
                    jump--;
                }
            }
        }
        else
        {
            prevButtonState = false;
        }
    }
    else if (playerID == 1)
    {
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
        {
            direction = 1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
        {
            direction = -1.0f;
        }

        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
        {
            if (!prevButtonState)
            {
                prevButtonState = true;
                if (jump > 0)
                {
                    if (jump == 2) velocity.y = firstJumpPower;
                    else velocity.y = secondJumpPower;
                    onPlatform = false;
                    jump--;
                }
            }
        }
        else
        {
            prevButtonState = false;
        }
    }

    velocity.x += direction * speed;
    velocity.x *= 0.92f;
}

bool Player::IsOverlapped()
{
    for (auto& platform : platforms)
    {
        if (Collision::AABB(this, platform.get()))
        {
            return true;
        }
    }
    return false;
}