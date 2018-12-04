#include "SDLGameObject.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject(const LoaderParams* pParams) : GameObject(pParams), position(float(pParams->GetX()), float(pParams->GetY())), velocity(0.0f, 0.0f), acceleration(0.0f, 0.0f)
{
    width = pParams->GetWidth();
    height = pParams->GetHeight();
    textureID = pParams->GetTextureID();
    currentRow = 1;
    currentFrame = 0;
}

void SDLGameObject::Draw()
{
    if (velocity.GetX() > 0)
    {
        TextureManager::Instance()->DrawFrame(textureID, int(position.GetX() + 0.5f), int(position.GetY() + 0.5f), width, height, currentRow, currentFrame, Game::Instance()->GetRenderer(), SDL_FLIP_HORIZONTAL);
    }
    else
    {
        TextureManager::Instance()->DrawFrame(textureID, int(position.GetX() + 0.5f), int(position.GetY() + 0.5f), width, height, currentRow, currentFrame, Game::Instance()->GetRenderer());

    }
}

void SDLGameObject::Update()
{
    velocity += acceleration;
    position += velocity;
}