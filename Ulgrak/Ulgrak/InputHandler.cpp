#include "InputHandler.h"
#include "Game.h"
#include "Camera.h"

InputHandler* InputHandler::pInstance = nullptr;

constexpr int joystickXDeadZone = 8000;
constexpr int joystickYDeadZone = 10000;

InputHandler::InputHandler() : mousePosition(0.0f, 0.0f)
{
    for (int i = 0; i < 3; i++)
    {
        mouseButtonStates.push_back(false);
    }
}

void InputHandler::Clean()
{
    if (controller != nullptr)
    {
        SDL_GameControllerClose(0);
    }
}

void InputHandler::Init()
{
    if (SDL_NumJoysticks() > 0)
    {
        controller = SDL_GameControllerOpen(0);
    }
}

void InputHandler::Reset()
{
}

bool InputHandler::IsKeyDown(SDL_Scancode key) const
{
    if (keyStates != 0)
    {
        if (keyStates[key] == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return false;
}

bool InputHandler::IsControllerButtonDown() const
{
    if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_A) == 1)
    {
        return true;
    }
    else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_B) == 1)
    {
        return true;
    }
    else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_X) == 1)
    {
        return true;
    }
    else if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_Y) == 1)
    {
        return true;
    }
    return false;
}

Vector2D InputHandler::GetMousePosition() const
{
    return mousePosition;
}

bool InputHandler::GetControllerAnalog(controller_buttons dir)
{
    switch (dir)
    {
    case CTRL_RIGHT:
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT) == 1)
        {
            return true;
        }
        if (controllerX > 0)
        {
            return true;
        }
        break;
    case CTRL_LEFT:
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT) == 1)
        {
            return true;
        }
        if (controllerX < 0)
        {
            return true;
        }
        break;
    case CTRL_UP:
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_UP) == 1)
        {
            return true;
        }
        if (controllerY > 0)
        {
            return true;
        }
        break;
    case CTRL_DOWN:
        if (SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN) == 1)
        {
            return true;
        }
        if (controllerY < 0)
        {
            return true;
        }
        break;
    default:
        break;
    }

    return false;
}

void InputHandler::Update()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            Game::Instance()->Quit();
            break;
        case SDL_KEYDOWN:
            keyStates = SDL_GetKeyboardState(NULL);
            break;
        case SDL_KEYUP:
            keyStates = SDL_GetKeyboardState(NULL);
            break;
        case SDL_MOUSEMOTION:
            OnMouseMove(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            OnMouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            OnMouseButtonUp(event);
            break;
        case SDL_JOYAXISMOTION:
            OnControllerMove(event);
        default:
            break;
        }
    }
}

void InputHandler::OnMouseMove(const SDL_Event& event)
{
    mousePosition.x = float(event.motion.x);
    mousePosition.y = float(event.motion.y);
}

void InputHandler::OnMouseButtonDown(const SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        mouseButtonStates[LEFT] = true;
    }
    else if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouseButtonStates[MIDDLE] = true;
    }
    else if (event.button.button == SDL_BUTTON_RIGHT)
    {
        mouseButtonStates[RIGHT] = true;
    }
}

void InputHandler::OnMouseButtonUp(const SDL_Event& event)
{
    if (event.button.button == SDL_BUTTON_LEFT)
    {
        mouseButtonStates[LEFT] = false;
    }
    else if (event.button.button == SDL_BUTTON_MIDDLE)
    {
        mouseButtonStates[MIDDLE] = false;
    }
    else if (event.button.button == SDL_BUTTON_RIGHT)
    {
        mouseButtonStates[RIGHT] = false;
    }
}

void InputHandler::OnControllerMove(const SDL_Event& event)
{
    if (event.jaxis.which == 0)
    {
        if (event.jaxis.axis == 0)
        {
            if (event.jaxis.value > joystickXDeadZone)
            {
                controllerX = 1;
            }
            else if (event.jaxis.value < -joystickXDeadZone)
            {
                controllerX = -1;
            }
            else
            {
                controllerX = 0;
            }
        }
        else
        {
            if (event.jaxis.value > joystickYDeadZone)
            {
                controllerY = -1;
            }
            else if (event.jaxis.value < -joystickYDeadZone)
            {
                controllerY = 1;
            }
            else
            {
                controllerY = 0;
            }
        }
    }
}