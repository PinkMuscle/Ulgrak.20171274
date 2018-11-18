#include "GameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

GameObject::GameObject(const LoaderParams* pParams) : position(float(pParams->GetX()), float(pParams->GetY()))
{
    width = pParams->GetWidth();
    height = pParams->GetHeight();
    textureID = pParams->GetTextureID();
    currentRow = 1;
    currentFrame = 0;
}

void GameObject::Draw()
{
    TextureManager::Instance()->DrawFrame(textureID, int(position.x + 0.5f), int(position.y + 0.5f), width, height, currentRow, currentFrame, Game::Instance()->GetRenderer());
}

void GameObject::Update()
{
    velocity += acceleration;
    position += velocity;
}