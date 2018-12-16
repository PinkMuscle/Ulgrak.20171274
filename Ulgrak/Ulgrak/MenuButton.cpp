#include "MenuButton.h"
#include "TextureManager.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams& pParams, void(*callback)()) : GameObject(pParams), callback(callback)
{
    released = false;
}

void MenuButton::Draw()
{
    TextureManager::Instance()->DrawFrame(textureID, int(position.x + 0.5f), int(position.y + 0.5f), width, height, currentRow, currentFrame, scale, SDL_FLIP_NONE);
}

void MenuButton::Update()
{
    Vector2D pMousePos = InputHandler::Instance()->GetMousePosition();
    if (pMousePos.x < (position.x + width * scale)
        && pMousePos.x > position.x
        && pMousePos.y < (position.y + height * scale)
        && pMousePos.y > position.y)
    {
        currentFrame = MOUSE_OVER;
        if (InputHandler::Instance()->GetMouseButtonState(LEFT) && released) {
            callback();
            released = false;
        }
        else if (!InputHandler::Instance()->GetMouseButtonState(LEFT)) {
            released = true;
        }
    }
    else {
        currentFrame = MOUSE_OUT;
        released = false;
    }
}