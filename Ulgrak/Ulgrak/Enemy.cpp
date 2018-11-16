#include "Enemy.h"
#include "InputHandler.h"

Enemy::Enemy(const LoaderParams* pParams) : SDLGameObject(pParams)
{
}

void Enemy::Draw()
{
    SDLGameObject::Draw();
}

void Enemy::Update()
{
	HandleInput();
    currentFrame = int(((SDL_GetTicks() / 100) % 6));
	SDLGameObject::Update();
}

void Enemy::Clean()
{
}

void Enemy::HandleInput()
{
	velocity = (InputHandler::Instance()->GetMousePosition() - position) / 100;

	if (InputHandler::Instance()->GetMouseButtonState(LEFT))
	{
		velocity += Vector2D(3.0f, 0.0f);
	}
}