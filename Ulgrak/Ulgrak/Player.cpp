#include "Player.h"
#include "InputHandler.h"
#include "Camera.h"

Player::Player(const LoaderParams& pParams, int id) : GameObject(pParams)
{
    playerID = id;
}

void Player::Draw()
{
    GameObject::Draw();
}

void Player::Update()
{
    HandleInput();
    //Camera::Instance()->Follow(position.GetX() - 432 + 45, 0.1f);
    currentFrame = int(((SDL_GetTicks() / 100) % 2));

    velocity += acceleration;
    position += velocity;
}

void Player::Clean()
{
    GameObject::Clean();
}

void Player::HandleInput()
{
    Vector2D direction;

    if (playerID == 0)
    {
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D))
        {
            direction.x = 1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A))
        {
            direction.x = -1.0f;
        }

        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_W))
        {
            direction.y = -1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_S))
        {
            direction.y = 1.0f;
        }
    }
    else if (playerID == 1)
    {
        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
        {
            direction.x = 1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
        {
            direction.x = -1.0f;
        }

        if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
        {
            direction.y = -1.0f;
        }
        else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
        {
            direction.y = 1.0f;
        }
    }

    velocity += direction.Normalized() * speed;
    velocity *= 0.92f;
}