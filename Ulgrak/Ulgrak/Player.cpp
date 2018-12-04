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
	HandleInput();
	currentFrame = int(((SDL_GetTicks() / 100) % 5));
	SDLGameObject::Update();
}

void Player::Clean()
{
}

void Player::HandleInput()
{
    Vector2D target = InputHandler::Instance()->GetMousePosition();
    velocity = (target - position) / 50;
}