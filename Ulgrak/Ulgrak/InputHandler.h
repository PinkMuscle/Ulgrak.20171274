#ifndef InputHandler_h
#define InputHandler_h
#include <SDL.h>
#include <vector>
#include "Vector2D.h"

enum mouse_buttons
{
	LEFT = 0,
	MIDDLE = 1,
	RIGHT = 2
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		if (pInstance == nullptr) {
			pInstance = new InputHandler();
		}
		return pInstance;
	}

	void Update();
	void Clean();
	bool IsKeyDown(SDL_Scancode key) const;
	bool GetMouseButtonState(mouse_buttons buttonNumber) const
	{
		return mouseButtonStates[buttonNumber];
	}
	Vector2D GetMousePosition() const
	{
		return mousePosition;
	}

private:
	InputHandler();
	~InputHandler() {}
	static InputHandler* pInstance;

	const Uint8* keyStates;
	std::vector<bool> mouseButtonStates;
	Vector2D mousePosition;

	void OnMouseMove(const SDL_Event& event);
	void OnMouseButtonDown(const SDL_Event& event);
	void OnMouseButtonUp(const SDL_Event& event);
	//void OnKeyDown(const SDL_Event& event);
	//void OnKeyUp(const SDL_Event& event);
};

#endif