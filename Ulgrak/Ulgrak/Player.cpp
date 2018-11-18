#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : GameObject(pParams)
{
}

void Player::Draw()
{
	GameObject::Draw();
}

void Player::Update()
{
	velocity = Vector2D(0.0f, 0.0f);
	HandleInput();
	currentFrame = int(((SDL_GetTicks() / 100) % 6));
	GameObject::Update();
}

void Player::Clean()
{
}

void Player::HandleInput()
{
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		velocity.x = 2;
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		velocity.x = -2;
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		velocity.y = -2;
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		velocity.y = 2;
	}
}