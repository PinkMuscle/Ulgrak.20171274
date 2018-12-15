#include "Player.h"
#include "InputHandler.h"
#include "Collision.h"
#include <iostream>

constexpr float speed = 0.2f;
constexpr float firstJumpPower = -3.0f;
constexpr float secondJumpPower = -3.6f;
constexpr float gravity = 0.07f;

Player::Player(const LoaderParams& pParams, std::vector<std::unique_ptr<GameObject>>& platforms_) : GameObject(pParams), platforms(platforms_)
{
    oldY = position.y;
}

void Player::Draw()
{
    GameObject::Draw();
}

void Player::Update()
{
    if (onPlatform)
    {
        position.y += 1;

        int platformCount = 0;
        int halfCount = 0;
        for (auto& platform : platforms)
        {
            if (Collision::AABB(this, platform.get()))
            {
                platformCount++;
                if (platform->GetTag() == "HALF")
                {
                    halfCount++;
                }
            }
        }
        if (platformCount == 0)
        {
            onPlatform = false;
            onHalfPlatform = false;
            jump = 1;
        }
        else if (platformCount == halfCount)
        {
            onHalfPlatform = true;
        }
        else
        {
            onHalfPlatform = false;
        }

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
        if (platform->GetTag() != "HALF" && Collision::AABB(this, platform.get()))
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
            if (platform->GetTag() == "HALF")
            {
                if (oldY + height * scale <= platform->GetPosition().y)
                {
                    position.y = platform->GetPosition().y - height * scale;
                    onPlatform = true;
                    jump = 2;
                    velocity.y = 0;
                }
            }
            else
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

    oldY = position.y;
}

void Player::Clean()
{
    GameObject::Clean();
}

void Player::HandleInput()
{
    float direction = 0.0f;

    if (tag == "1P")
    {
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D))
        {
            currentFrame = int(((SDL_GetTicks() / 100) % 2));
            direction = 1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A))
        {
            currentFrame = int(((SDL_GetTicks() / 100) % 2));
            direction = -1.0f;
        }
        else
        {
            currentFrame = 0;
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
                    onHalfPlatform = false;
                    jump--;
                }
            }
        }
        else
        {
            prevButtonState = false;
        }

        if (onHalfPlatform && InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_S))
        {
            onPlatform = false;
            onHalfPlatform = false;
            jump = 1;
            position.y += 1;
            oldY += 1;
        }
    }
    else if (tag == "2P")
    {
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
        {
            currentFrame = int(((SDL_GetTicks() / 100) % 2));
            direction = 1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
        {
            currentFrame = int(((SDL_GetTicks() / 100) % 2));
            direction = -1.0f;
        }
        else
        {
            currentFrame = 0;
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
                    onHalfPlatform = false;
                    jump--;
                }
            }
        }
        else
        {
            prevButtonState = false;
        }

        if (onHalfPlatform && InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
        {
            onPlatform = false;
            onHalfPlatform = false;
            jump = 1;
            position.y += 1;
            oldY += 1;
        }
    }

    velocity.x += direction * speed;
    velocity.x *= 0.92f;
}