#ifndef Game_h
#define Game_h
#include "SDL.h"
#include "SDL_image.h"

class Game
{
public:
    Game() {}
    ~Game() {}

    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handleEvents();
    void update();
    void render();
    void clean();

    bool running();

    static SDL_Event event;
    static SDL_Renderer* renderer;
    static float deltaTime;

private:
    bool isRunning;
    Uint32 oldTicks;
    SDL_Window* window;

    void SetDeltaTime();
};

#endif