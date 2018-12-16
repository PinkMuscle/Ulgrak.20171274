#include "PauseState.h"
#include "States.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "MenuButton.h"
#include <iostream>

PauseState* PauseState::pInstance = nullptr;
const std::string PauseState::pauseID = "PAUSE";

bool PauseState::OnEnter()
{
    if (!TextureManager::Instance()->Load("Assets/restart.png", "restart"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/mainmenu.png", "mainmenu"))
    {
        return false;
    }

    gameObjects.emplace_back(std::make_unique<MenuButton>(LoaderParams(864 / 2 - 100, 180, 56, 12, 4, "restart"), Restart));
    gameObjects.emplace_back(std::make_unique<MenuButton>(LoaderParams(864 / 2 - 100, 270, 56, 12, 4, "mainmenu"), PauseToMain));

    std::cout << "entering PauseState\n";

    return true;
}

bool PauseState::OnExit()
{
    gameObjects.clear();
    TextureManager::Instance()->ClearFromTextureMap("restart");
    TextureManager::Instance()->ClearFromTextureMap("mainmenu");
    InputHandler::Instance()->Reset();
    std::cout << "exiting PauseState\n";

    return true;
}

void PauseState::PauseToMain()
{
    Game::Instance()->GetStateMachine()->ChangeState(MenuState::Instance());
}

void PauseState::Restart()
{
    Game::Instance()->GetStateMachine()->PopState();
}