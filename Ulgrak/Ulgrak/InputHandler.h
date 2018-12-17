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

enum controller_buttons
{
    CTRL_RIGHT = 0,
    CTRL_LEFT = 1,
    CTRL_UP = 2,
    CTRL_DOWN = 3
};

class InputHandler
{
public:
	~InputHandler() {}
	static InputHandler* Instance()
	{
		if (pInstance == nullptr) {
			pInstance = new InputHandler();
		}
		return pInstance;
	}

	void Update();
	void Clean();
    void Init();
    void Reset();
	bool IsKeyDown(SDL_Scancode key) const;
	bool IsControllerButtonDown() const;
	bool GetMouseButtonState(mouse_buttons buttonNumber) const
	{
		return mouseButtonStates[buttonNumber];
	}
    Vector2D GetMousePosition() const;
    bool GetControllerAnalog(controller_buttons dir);
    

private:
	InputHandler();
	static InputHandler* pInstance;

	const Uint8* keyStates;
	std::vector<bool> mouseButtonStates;
	Vector2D mousePosition;
    SDL_GameController* controller = nullptr;
    int controllerX = 0, controllerY = 0;

	void OnMouseMove(const SDL_Event& event);
	void OnMouseButtonDown(const SDL_Event& event);
	void OnMouseButtonUp(const SDL_Event& event);
    void OnControllerMove(const SDL_Event& event);
};

#endif