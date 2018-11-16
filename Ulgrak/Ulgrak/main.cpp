#include "Game.h"
#include <iostream>

void FrameDelay(int maxFPS);

int main(int argc, char* argv[])
{
    std::cout << "Game Init Attempt...\n";
    if (!Game::Instance()->Init("PP14.MInputHandler", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, false))
    {
        std::cout << "Game Init Failure - " << SDL_GetError() << std::endl;
        return -1;
    }

    std::cout << "Game Init Success!\n";
    while (Game::Instance()->IsRunning())
    {
        Game::Instance()->HandleEvents();
        Game::Instance()->Update();
        Game::Instance()->Render();
		FrameDelay(144);
    }

    std::cout << "Closing Game...\n";
    Game::Instance()->Clean();

    return 0;
}
void FrameDelay(int maxFPS)
{
	static Uint32 frameStart;
	int latency = int((float)1000 / maxFPS + 0.5f);
	int frameTime = SDL_GetTicks() - frameStart;

	if (frameTime < latency)
	{
		SDL_Delay(latency - frameTime);
	}
	frameStart = SDL_GetTicks();
}