#include "Player.h"
#include "TextureManager.h"
#include <iostream>

Player::Player()
{
    texture = TextureManager::LoadTexture("../assets/Player.png", Game::renderer);
    srcRect.w = 32;
    srcRect.h = 32;
    dstRect.w = srcRect.w * 2;
    dstRect.h = srcRect.h * 2;
    srcRect.x = srcRect.y = 0;
}

Player::~Player()
{
    SDL_DestroyTexture(texture);
}

void Player::GetBoxes(Box** boxes, int num)
{
    this->boxes = boxes;
    this->boxNum = num;
}

void Player::Move()
{
    if (Game::event.type == SDL_KEYDOWN)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_w: //Up
            jump = 1;
            break;
        case SDLK_s: //Down
            break;
        case SDLK_d: //Right
            xvel = speed * Game::deltaTime;
            break;
        case SDLK_a: //Left
            xvel = -1 * speed * Game::deltaTime;
            break;
        default:
            break;
        }
    }
    if (Game::event.type == SDL_KEYUP)
    {
        switch (Game::event.key.keysym.sym)
        {
        case SDLK_w: //Up
            jump = 0;
            break;
        case SDLK_s: //Down
            break;
        case SDLK_d: //Right
            if (xvel > 0)
            {
                xvel = 0;
                srcRect.x = 0;
            }
            break;
        case SDLK_a: //Left
            if (xvel < 0)
            {
                xvel = 0;
                srcRect.x = 0;
            }
            break;
        default:
            break;
        }
    }

    if (xvel != 0)
    {
        x += xvel;
        if (Collision())
        {
            x -= xvel;
        }

        srcRect.x = 32 * (SDL_GetTicks() / 100 % 2);
    }

    if (test = isOnPlatform())
    {
        if (jump == 1)
        {
            yvel = -jumpHeight;
        }
    }
    else
    {
        yvel += gravity * Game::deltaTime;
    }

    y += yvel * Game::deltaTime;
    if (Collision())
    {
        yvel = 0;
        while (Collision())
        {
            y -= 1.0f;
        }
    }
}

void Player::Render()
{
    dstRect.x = int(x + 0.5f);
    dstRect.y = int(y + 0.5f);
    std::cout << "yvel: " << yvel << " / " << "isOnPlatform: " << test << " / " << "deltaTime: " << Game::deltaTime << std::endl;
    SDL_RenderCopy(Game::renderer, texture, &srcRect, &dstRect);
}

bool Player::Collision()
{
    SDL_Rect tempRect;
    for (int i = 0; i < boxNum; i++)
    {
        tempRect = boxes[i]->GetRect();
        if (
            x + dstRect.w > tempRect.x &&
            y + dstRect.h > tempRect.y &&
            x < tempRect.x + tempRect.w &&
            y < tempRect.y + tempRect.h
            )
        {
            return true;
        }
    }

    return false;
}

bool Player::isOnPlatform()
{
    y += 1.0f;
    if (Collision())
    {
        y -= 1.0f;
        return true;
    }
    else
    {
        y -= 1.0f;
        return false;
    }
}