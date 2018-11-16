#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Player::Draw()
{
	SDLGameObject::Draw();
}

void Player::Update()
{
	velocity = Vector2D(0.0f, 0.0f);
	HandleInput();
	currentFrame = int(((SDL_GetTicks() / 100) % 6));
	SDLGameObject::Update();
}

void Player::Clean()
{
}

void Player::HandleInput()
{
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT))
	{
		velocity.SetX(2);
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT))
	{
		velocity.SetX(-2);
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP))
	{
		velocity.SetY(-2);
	}
	if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
	{
		velocity.SetY(2);
	}
}