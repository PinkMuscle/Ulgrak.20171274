#include "PlayState.h"
#include "States.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Camera.h"
#include "TextPrinter.h"
#include "Collision.h"
//Objects
#include "Background.h"
#include "Player.h"
#include "Platform.h"
//Standard
#include <iostream>
#include <algorithm>

PlayState* PlayState::pInstance = nullptr;
const std::string PlayState::playID = "PLAY";

void PlayState::Update()
{
    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->GetStateMachine()->ChangeState(PauseState::Instance());
        return;
    }

    background->Update();
    for (auto& objects : players)
    {
        objects->Update();
    }
    for (auto& objects : projectiles)
    {
        objects->Update();
    }
    for (auto& objects : ui)
    {
        objects->Update();
    }

    CheckCollision();
    Refresh();
    Camera::Instance()->Update(players);
}

void PlayState::Render()
{
    background->Draw();
    for (auto& objects : platforms)
    {
        objects->Draw();
    }
    for (auto& objects : players)
    {
        objects->Draw();
    }
    for (auto& objects : projectiles)
    {
        objects->Draw();
    }
    for (auto& objects : ui)
    {
        objects->Draw();
    }

    ////타이머 표시
    //TextPrinter::Instance()->Draw(Timer::Instance()->GetTime(), 180, 28, 5);
}

bool PlayState::OnEnter()
{
    if (!TextureManager::Instance()->Load("Assets/background.png", "background"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player.png", "player"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/platform.png", "platform"))
    {
        return false;
    }

    background = std::make_unique<Background>(LoaderParams(-1296 + 256, -810, 1728, 1080, 1.5f, "background"));

    players.emplace_back(std::make_unique<Player>(LoaderParams(100, 20, 32, 32, "player"), platforms, 0));
    players.emplace_back(std::make_unique<Player>(LoaderParams(400, 20, 32, 32, "player"), platforms, 1));

    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(0, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(128, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(256, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(384, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(64, 100 - 128, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(320, 100 - 128, 32, 8, 4, "platform")));

    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::OnExit()
{
    background.reset();
    platforms.clear();
    players.clear();
    projectiles.clear();
    ui.clear();

    TextureManager::Instance()->ClearFromTextureMap("background");
    TextureManager::Instance()->ClearFromTextureMap("player");
    TextureManager::Instance()->ClearFromTextureMap("platform");

    std::cout << "exiting PlayState\n";

    return true;
}

void PlayState::CheckCollision()
{
    //for (auto& player : players)
    //{
    //    for (auto& platform : platforms)
    //    {
    //        if (Collision::AABB(player.get(), platform.get()))
    //        {
    //            Vector2D playerPos = player->GetPosition();
    //            Vector2D platformPos = platform->GetPosition();
    //            Vector2D reboundDir = (player->GetVelocity() * (-1)).Normalized();
    //            Vector2D edge = platformPos;

    //            if (reboundDir.x > 0)
    //            {
    //                edge.x += platform->GetWidth();
    //            }
    //            if (reboundDir.y > 0)
    //            {
    //                edge.y += platform->GetHeight();
    //            }

    //            if ((edge.x - playerPos.x) / reboundDir.x < (edge.y - playerPos.y) / reboundDir.y)
    //            {   

    //            }

    //            break;
    //        }
    //    }
    //}

    //for (auto& e : enemies)
    //{
    //    if (Collision::AABB(e.get(), player.get()))
    //    {
    //        e->Destroy();
    //        player->Destroy();
    //        Game::Instance()->GetStateMachine()->ChangeState(GameOverState::Instance());
    //        return;
    //    }
    //    for (auto& a : animals)
    //    {
    //        if (Collision::AABB(e.get(), a.get()))
    //        {
    //            auto ani = dynamic_cast<Animal*>(a.get());
    //            auto ene = dynamic_cast<Enemy*>(e.get());
    //            if (ani->GetState() == FREE && ene->GetState() == HUNT)
    //            {
    //                ani->HuntedBy(ene);
    //                ene->SetStateRun();
    //                ene->SetAnimal(ani);
    //                break;
    //            }
    //        }
    //    }
    //}
}

void PlayState::Refresh()
{
    platforms.erase
    (
        std::remove_if(std::begin(platforms), std::end(platforms), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
        std::end(platforms)
    );
    players.erase
    (
        std::remove_if(std::begin(players), std::end(players), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
        std::end(players)
    );
    projectiles.erase
    (
        std::remove_if(std::begin(projectiles), std::end(projectiles), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
        std::end(projectiles)
    );
}