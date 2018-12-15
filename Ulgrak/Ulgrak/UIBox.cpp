#include "UIBox.h"
#include "TextureManager.h"

UIBox::UIBox(const LoaderParams& pParams) : GameObject(pParams)
{
}

void UIBox::Draw()
{
    TextureManager::Instance()->Draw(textureID, int(position.x + 0.5f), int(position.y + 0.5f), width, height, scale, SDL_FLIP_NONE);
}

void UIBox::Update()
{

}