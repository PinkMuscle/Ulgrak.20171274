#include "UIBox.h"
#include "TextureManager.h"

UIBox::UIBox(const LoaderParams& pParams) : GameObject(pParams)
{
}

void UIBox::Draw()
{
    TextureManager::Instance()->Draw(textureID, int(position.x), int(position.y), width, height, scale, SDL_FLIP_NONE);
}

void UIBox::Update()
{

}