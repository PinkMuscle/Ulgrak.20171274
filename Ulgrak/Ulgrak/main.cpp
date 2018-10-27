#pragma comment(linker , "/entry:WinMainCRTStartup /subsystem:console")
#include "Game.h"

void FrameDelay(int maxFPS);
Game* game = 0;

int main(int argc, char* argv[])
{

    game = new Game();
    game->init("Ulgrak", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 960, 720, false);

    while (game->running())
    {
        game->handleEvents();
        game->update();
        game->render();
        FrameDelay(144);
    }
    game->clean();

    return 0;
}

void FrameDelay(int maxFPS)
{
    static const int latency = int((float)1000 / maxFPS + 0.5f);
    static unsigned int frameStart;
    static int frameTime;

    frameTime = SDL_GetTicks() - frameStart;
    if (frameTime < latency)
    {
        SDL_Delay(latency - frameTime);
    }
    frameStart = SDL_GetTicks();
}