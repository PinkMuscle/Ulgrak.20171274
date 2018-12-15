#include "GameState.h"

void GameState::Update()
{
    for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Update();
    }
}

void GameState::Render()
{
    for (std::vector<std::unique_ptr<GameObject>>::size_type i = 0; i < gameObjects.size(); i++)
    {
        gameObjects[i]->Draw();
    }
}