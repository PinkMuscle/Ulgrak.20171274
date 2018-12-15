#include "InputHandler.h"
#include "Game.h"
#include "Camera.h"

InputHandler* InputHandler::pInstance = nullptr;

InputHandler::InputHandler() : mousePosition(0.0f, 0.0f)
{
	for (int i = 0; i < 3; i++)
	{
		mouseButtonStates.push_back(false);
	}
}

void InputHandler::Clean()
{
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

Vector2D InputHandler::GetMousePosition() const
{
    return mousePosition;
}

Vector2D InputHandler::GetMousePositionOnCamera() const
{
    return mousePosition + Vector2D(Camera::Instance()->GetX(), 0);
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