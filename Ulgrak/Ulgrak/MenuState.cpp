#include "MenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "PlayState.h"
#include <iostream>

MenuState* MenuState::pInstance = nullptr;
const std::string MenuState::menuID = "MENU";

bool MenuState::OnEnter()
{
    if (!TextureManager::Instance()->Load("../assets/button.png", "playbutton", Game::Instance()->GetRenderer()))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("../assets/exit.png", "exitbutton", Game::Instance()->GetRenderer()))
    {
        return false;
    }
    GameObject* button1 = new MenuButton(new LoaderParams(100, 100, 400, 100, "playbutton"), MenuToPlay);
    GameObject* button2 = new MenuButton(new LoaderParams(100, 300, 400, 100, "exitbutton"), ExitFromMenu);
    gameObjects.push_back(button1);
    gameObjects.push_back(button2);
    std::cout << "entering MenuState\n";

    return true;
}

bool MenuState::OnExit()
{
    for (std::vector<GameObject*>::size_type i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Clean();
    }
    gameObjects.clear();
    TextureManager::Instance()->ClearFromTextureMap("playbutton");
    TextureManager::Instance()->ClearFromTextureMap("exitbutton");
    std::cout << "exiting MenuState\n";

    return true;
}

void MenuState::MenuToPlay()
{
    Game::Instance()->GetStateMachine()->ChangeState(PlayState::Instance());
}

void MenuState::ExitFromMenu()
{
    Game::Instance()->Quit();
}