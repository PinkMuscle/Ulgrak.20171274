#include "Game.h"
#include "Player.h"
#include "Box.h"
#define BOX_NUM 5

SDL_Event Game::event;
SDL_Renderer* Game::renderer = nullptr;
float Game::deltaTime;

Player* player;
Box* box[BOX_NUM];

bool Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    else
    {
        flags = SDL_WINDOW_SHOWN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window != 0)
        {
            renderer = SDL_CreateRenderer(window, -1, 0);
        }

        oldTicks = SDL_GetTicks();
        player = new Player();
        box[0] = new Box(0, 500, 256, 64);
        box[1] = new Box(256, 500, 64, 128);
        box[2] = new Box(320, 564, 512, 64);
        box[3] = new Box(832, 320, 64, 308);
        box[4] = new Box(896, 320, 64, 64);
        player->GetBoxes(box, BOX_NUM);

        isRunning = true;
    }
    else
    {
        isRunning = false;
    }

    return isRunning;
}

void Game::handleEvents()
{

    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
        }
    }
}

void Game::update()
{
    SetDeltaTime();

    player->Move();
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    player->Render();
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    for (int i = 0; i < BOX_NUM; i++)
    {
        box[i]->Render();
    }

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    player->~Player();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

bool Game::running()
{
    return isRunning;
}

void Game::SetDeltaTime()
{
    deltaTime = (float)(SDL_GetTicks() - oldTicks) / 1000;
    oldTicks = SDL_GetTicks();
}