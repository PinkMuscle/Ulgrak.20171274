#include "Player.h"
#include "InputHandler.h"
#include "Camera.h"

Player::Player(const LoaderParams& pParams) : GameObject(pParams)
{
}

void Player::Draw()
{
    GameObject::Draw();
}

void Player::Update()
{
    HandleInput();
    //Camera::Instance()->Follow(position.GetX() - 432 + 45, 0.1f);
    currentFrame = int(((SDL_GetTicks() / 100) % 5));

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

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) || InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_D))
    {
        direction.x = 1.0f;
    }
    else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) || InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_A))
    {
        direction.x = -1.0f;
    }

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) || InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_W))
    {
        direction.y = -1.0f;
    }
    else if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN) || InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_S))
    {
        direction.y = 1.0f;
    }

    velocity += direction.Normalized() * speed;
    velocity *= 0.92f;

    if (position.y > 400)
    {
        velocity.y = 0;
        position.y = 400;
    }
    else if (position.y < 0)
    {
        velocity.y = 0;
        position.y = 0;
    }
}