#include "MenuState.h"
#include "Game.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "UIBox.h"
#include "PlayState.h"
#include <iostream>

MenuState* MenuState::pInstance = nullptr;
const std::string MenuState::menuID = "MENU";

bool MenuState::OnEnter()
{
    if (!TextureManager::Instance()->Load("Assets/background.png", "background"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/2p_play.png", "2p_play"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/3p_play.png", "3p_play"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/exit.png", "exit"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/title.png", "title"))
    {
        return false;
    }

    gameObjects.emplace_back(std::make_unique<UIBox>(LoaderParams(0, 0, 1728, 1080, "background"), 800, 2));
    gameObjects.emplace_back(std::make_unique<MenuButton>(LoaderParams(520, 170, 47, 12, 4, "2p_play"), MenuToPlay));
    gameObjects.emplace_back(std::make_unique<MenuButton>(LoaderParams(520, 240, 47, 12, 4, "3p_play"), MenuToPlay));
    gameObjects.emplace_back(std::make_unique<MenuButton>(LoaderParams(520, 310, 47, 12, 4, "exit"), ExitFromMenu));
    gameObjects.emplace_back(std::make_unique<UIBox>(LoaderParams(160, 180, 100, 54, 3, "title")));

    std::cout << "entering MenuState\n";

    return true;
}

bool MenuState::OnExit()
{
    gameObjects.clear();
    TextureManager::Instance()->ClearFromTextureMap("background");
    TextureManager::Instance()->ClearFromTextureMap("2p_play");
    TextureManager::Instance()->ClearFromTextureMap("3p_play");
    TextureManager::Instance()->ClearFromTextureMap("exit");
    TextureManager::Instance()->ClearFromTextureMap("title");
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