#ifndef Game_h
#define Game_h
#include <SDL.h>
#include <vector>
#include "GameObject.h"
#include "GameStateMachine.h"

class Game
{
public:
	~Game() {}
    static Game* Instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new Game();
        }
        return pInstance;
    }

	bool Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
	void Render();
    void Update();
	void HandleEvents();
	void Quit();
	void Clean();
	bool IsRunning() const { return running; }
    SDL_Renderer* GetRenderer() const { return pRenderer; }
    GameStateMachine* GetStateMachine() const { return pGameStateMachine; }

private:
	Game() {}
    static Game* pInstance;

	SDL_Window* pWindow;
	SDL_Renderer* pRenderer;
	bool running;

    std::vector<GameObject*> gameObjects;
    GameStateMachine* pGameStateMachine;
};

#endif Game_h