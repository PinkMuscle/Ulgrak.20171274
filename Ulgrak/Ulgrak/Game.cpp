#include "Game.h"
#include "TextureManager.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "Player.h"
#include <SDL_image.h>
#include <iostream>

Game* Game::pInstance = nullptr;

bool Game::Init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
    {
        Uint32 flags;
        if (fullscreen)
        {
            flags = SDL_WINDOW_FULLSCREEN_DESKTOP;
        }
        else
        {
            flags = SDL_WINDOW_SHOWN;
        }

        pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (pWindow != 0)
        {
            pRenderer = SDL_CreateRenderer(pWindow, -1, 0);
        }

        SDL_SetRenderDrawColor(pRenderer, 0, 40, 60, 255);
        if (!TextureManager::Instance()->Load("../Assets/animate-alpha.png", "animate", pRenderer))
        {
            return false;
        }

        gameObjects.push_back(new Player(new LoaderParams(100, 100, 128, 82, "animate")));

        running = true;
    }
    else
    {
        running = false;
    }
    return running;
}

void Game::Render()
{
    SDL_RenderClear(pRenderer);
    for (auto const& i : gameObjects)
    {
        i->Draw();
    }
    SDL_RenderPresent(pRenderer);
}

void Game::Update()
{
    for (auto const& i : gameObjects)
    {
        i->Update();
    }
}

void Game::Quit()
{
	running = false;
}

void Game::Clean()
{
    std::cout << "cleaning game\n";
	InputHandler::Instance()->Clean();
    SDL_DestroyWindow(pWindow);
    SDL_DestroyRenderer(pRenderer);
    SDL_Quit();
}

void Game::HandleEvents()
{
	InputHandler::Instance()->Update();
}