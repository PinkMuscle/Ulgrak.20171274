#include "MenuButton.h"
#include "InputHandler.h"

MenuButton::MenuButton(const LoaderParams* pParams, void(*callback)()) : SDLGameObject(pParams), callback(callback)
{

}

void MenuButton::Draw()
{
    SDLGameObject::Draw(); // use the base class drawing
}

void MenuButton::Update()
{
    Vector2D* pMousePos = &(InputHandler::Instance()->GetMousePosition());
    if (pMousePos->GetX() < (position.GetX() + width)
        && pMousePos->GetX() > position.GetX()
        && pMousePos->GetY() < (position.GetY() + height)
        && pMousePos->GetY() > position.GetY())
    {
        if (InputHandler::Instance()->GetMouseButtonState(LEFT) && released) {
            currentFrame = CLICKED;
            callback();
            released = false;
        }
        else if (!InputHandler::Instance()->GetMouseButtonState(LEFT)) {
            released = true;
            currentFrame = MOUSE_OVER;
        }
    }
    else {
        currentFrame = MOUSE_OUT;
    }
}

void MenuButton::Clean()
{
    SDLGameObject::Clean();
}