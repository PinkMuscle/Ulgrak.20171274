#include "PlayState.h"
#include "States.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "SDLGameObject.h"
#include "Player.h"
#include "Enemy.h"
#include <iostream>

PlayState* PlayState::pInstance = nullptr;
const std::string PlayState::playID = "PLAY";

void PlayState::Update()
{
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->GetStateMachine()->ChangeState(PauseState::Instance());
    }
    for (std::vector<GameObject*>::size_type i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Update();
    }
    if (CheckCollision(dynamic_cast<SDLGameObject*>(gameObjects[0]), dynamic_cast<SDLGameObject*>(gameObjects[1])))
    {
        Game::Instance()->GetStateMachine()->ChangeState(GameOverState::Instance());
    }
}

bool PlayState::OnEnter()
{
    if (!TextureManager::Instance()->Load("../assets/helicopter.png", "helicopter", Game::Instance()->GetRenderer()))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("../assets/helicopter2.png", "helicopter2", Game::Instance()->GetRenderer()))
    {
        return false;
    }

    GameObject* player = new Player(new LoaderParams(100, 100, 128, 55, "helicopter"));
    GameObject* enemy = new Enemy(new LoaderParams(300, 300, 128, 55, "helicopter2"));

    gameObjects.push_back(player);
    gameObjects.push_back(enemy);

    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::OnExit()
{
    for (std::vector<GameObject*>::size_type i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Clean();
    }
    gameObjects.clear();

    TextureManager::Instance()->ClearFromTextureMap("helicopter");
    std::cout << "exiting PlayState\n";

    return true;
}

bool PlayState::CheckCollision(SDLGameObject* p1, SDLGameObject* p2)
{
    float leftA, leftB;
    float rightA, rightB;
    float topA, topB;
    float bottomA, bottomB;

    leftA = p1->GetPosition().GetX();
    rightA = p1->GetPosition().GetX() + p1->GetWidth();
    topA = p1->GetPosition().GetY();
    bottomA = p1->GetPosition().GetY() + p1->GetHeight();

    //Calculate the sides of rect B
    leftB = p2->GetPosition().GetX();
    rightB = p2->GetPosition().GetX() + p2->GetWidth();
    topB = p2->GetPosition().GetY();
    bottomB = p2->GetPosition().GetY() + p2->GetHeight();

    //If any of the sides from A are outside of B
    if (bottomA <= topB) { return false; }
    if (topA >= bottomB) { return false; }
    if (rightA <= leftB) { return false; }
    if (leftA >= rightB) { return false; }

    return true;
}