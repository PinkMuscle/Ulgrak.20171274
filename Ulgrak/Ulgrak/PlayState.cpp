#include "PlayState.h"
#include "States.h"
#include "Game.h"
#include "TextureManager.h"
#include "InputHandler.h"
#include "Camera.h"
#include "TextPrinter.h"
#include "Collision.h"
//Objects
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
    //if (animals.size() == 0)
    //{
    //	Game::Instance()->GetStateMachine()->ChangeState(GameOverState::Instance());
    //	return;
    //}
 //   if (SDL_GetTicks() > nextSpawn)
 //   {
 //       enemies.emplace_back(std::make_unique<Enemy>(LoaderParams((rand() % 10) * 100, -100, 128, 55, 0.7f, "helicopter2")));
 //       nextSpawn = SDL_GetTicks() + spawnDelay;
 //       if (spawnDelay > 800)
 //       {
 //           spawnDelay = spawnDelay - 40u;
 //       }
 //   }

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
    //if (!TextureManager::Instance()->Load("../assets/minigame_background.png", "background"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/helicopter.png", "helicopter"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/helicopter2.png", "helicopter2"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/animate-alpha.png", "animal"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/missile.png", "missile"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/explosion.png", "explosion"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/carrcass.png", "carrcass"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/aim.png", "aim"))
    //{
    //    return false;
    //}
    //if (!TextureManager::Instance()->Load("../assets/scoreboard.png", "scoreboard"))
    //{
    //    return false;
    //}
    if (!TextureManager::Instance()->Load("Assets/player.png", "player"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/platform.png", "platform"))
    {
        return false;
    }

    players.emplace_back(std::make_unique<Player>(LoaderParams(200, 320, 32, 32, "player"), 0));
    players.emplace_back(std::make_unique<Player>(LoaderParams(500, 320, 32, 32, "player"), 1));

    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(100, 400, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(100 + 128, 400, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(100 + 256, 400, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(100 + 384, 400, 32, 8, 4, "platform")));

    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(100 + 64, 400 - 128, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(100 + 320, 400 - 128, 32, 8, 4, "platform")));


    //backgrounds[0] = std::make_unique<Background>(LoaderParams(0, 0, 432, 270, 2, "background"));
    //backgrounds[1] = std::make_unique<Background>(LoaderParams(864, 0, 432, 270, 2, "background"));
    //player = std::make_unique<Player>(LoaderParams(100, 100, 128, 55, 0.7f, "helicopter"));
    //ui.emplace_back(std::make_unique<Aim>(LoaderParams(0, 0, 11, 11, 3, "aim")));
    //ui.emplace_back(std::make_unique<UIBox>(LoaderParams(0, 0, 360, 100, 1, "scoreboard")));
    //for (int i = 0; i < 8; i++)
    //{
    //    animals.emplace_back(std::make_unique<Animal>(LoaderParams(i * 100, 400, 128, 82, "animal")));
    //}

    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::OnExit()
{
    /*player.reset();*/
    platforms.clear();
    players.clear();
    projectiles.clear();
    ui.clear();

    //TextureManager::Instance()->ClearFromTextureMap("background");
    //TextureManager::Instance()->ClearFromTextureMap("helicopter");
    //TextureManager::Instance()->ClearFromTextureMap("helicopter2");
    //TextureManager::Instance()->ClearFromTextureMap("animal");
    //TextureManager::Instance()->ClearFromTextureMap("missile");
    //TextureManager::Instance()->ClearFromTextureMap("explosion");
    //TextureManager::Instance()->ClearFromTextureMap("carrcass");
    //TextureManager::Instance()->ClearFromTextureMap("aim");

    std::cout << "exiting PlayState\n";

    return true;
}

void PlayState::CheckCollision()
{
    //for (auto& player : players)
    //{
    //    for (auto& platform : platforms)
    //    {
    //        if (Collision::AABB(m.get(), e.get()))
    //        {
    //            Vector2D enemyPos = dynamic_cast<SDLGameObject*>(e.get())->GetPosition();
    //            m->Destroy();
    //            e->Destroy();
    //            effects.emplace_back(std::make_unique<Explosion>(LoaderParams(int(enemyPos.GetX()), int(enemyPos.GetY()) - 16, 64, 64, 1.5f, "explosion")));
    //            break;
    //        }
    //    }
    //    for (auto& a : players)
    //    {
    //        if (Collision::AABB(m.get(), a.get()))
    //        {
    //            Vector2D animalPos = dynamic_cast<SDLGameObject*>(a.get())->GetPosition();
    //            m->Destroy();
    //            a->Destroy();
    //            effects.emplace_back(std::make_unique<Carrcass>(LoaderParams(int(animalPos.GetX()), int(animalPos.GetY()), 128, 82, 0.8f, "carrcass")));
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