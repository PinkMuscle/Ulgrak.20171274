#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")
#include "Game.h"

Game* game = 0;

int main(int argc, char* argv[])
{
    const int MaxFPS = 144;
    const int frameDelay = 1000 / MaxFPS;

    Uint32 frameStart;
    int frameTime;

    game = new Game();
    game->init("Ulgrak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 720, false);

    while (game->running())
    {
        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < frameDelay)
        {
            SDL_Delay(frameDelay - frameTime);
        }
    }
    game->clean();

    return 0;
}