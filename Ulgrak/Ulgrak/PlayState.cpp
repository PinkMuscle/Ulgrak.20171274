//#include "PlayState.h"
//#include "States.h"
//#include "Game.h"
//#include "TextureManager.h"
//#include "InputHandler.h"
//#include "Camera.h"
//#include "Timer.h"
//#include "Collision.h"
////Objects
//#include "Player.h"
//#include "Enemy.h"
//#include "Animal.h"
//#include "Missile.h"
//#include "Aim.h"
//#include "Background.h"
//#include "Explosion.h"
//#include "Carrcass.h"
//#include "UIBox.h"
////Standard
//#include <iostream>
//#include <algorithm>
//
//PlayState* PlayState::pInstance = nullptr;
//const std::string PlayState::playID = "PLAY";
//
//void PlayState::Update()
//{
//    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
//    {
//        Game::Instance()->GetStateMachine()->ChangeState(PauseState::Instance());
//        return;
//    }
//	if (animals.size() == 0)
//	{
//		Game::Instance()->GetStateMachine()->ChangeState(GameOverState::Instance());
//		return;
//	}
//    if (SDL_GetTicks() > nextSpawn)
//    {
//        enemies.emplace_back(std::make_unique<Enemy>(LoaderParams((rand() % 10) * 100, -100, 128, 55, 0.7f, "helicopter2")));
//        nextSpawn = SDL_GetTicks() + spawnDelay;
//        if (spawnDelay > 800)
//        {
//            spawnDelay = spawnDelay - 40u;
//        }
//    }
//    projectiles->HandleInput();
//
//    for (auto& objects : backgrounds)
//    {
//        objects->Update();
//    }
//    player->Update();
//    for (auto& objects : enemies)
//    {
//        objects->Update();
//    }
//    for (auto& objects : animals)
//    {
//        objects->Update();
//    }
//    for (auto& objects : missiles)
//    {
//        objects->Update();
//    }
//    for (auto& objects : effects)
//    {
//        objects->Update();
//    }
//    for (auto& objects : ui)
//    {
//        objects->Update();
//    }
//
//    CheckCollision();
//    Refresh();
//}
//
//void PlayState::Render()
//{
//    for (auto& objects : backgrounds)
//    {
//        objects->Draw();
//    }
//    for (auto& objects : effects)
//    {
//        objects->Draw();
//    }
//    player->Draw();
//    for (auto& objects : enemies)
//    {
//        objects->Draw();
//    }
//    for (auto& objects : animals)
//    {
//        objects->Draw();
//    }
//    for (auto& objects : missiles)
//    {
//        objects->Draw();
//    }
//    for (auto& objects : ui)
//    {
//        objects->Draw();
//    }
//    //남은 동물 수 표시
//    TextureManager::Instance()->Draw("animal", 12, 12, 128, 82, 0.8f);
//    TextPrinter::Instance()->Draw("x" + std::to_string(animals.size()), 88, 32, 4);
//    //타이머 표시
//    TextPrinter::Instance()->Draw(Timer::Instance()->GetTime(), 180, 28, 5);
//}
//
//bool PlayState::OnEnter()
//{
//    if (!TextureManager::Instance()->Load("../assets/minigame_background.png", "background"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/helicopter.png", "helicopter"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/helicopter2.png", "helicopter2"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/animate-alpha.png", "animal"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/missile.png", "missile"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/explosion.png", "explosion"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/carrcass.png", "carrcass"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/aim.png", "aim"))
//    {
//        return false;
//    }
//    if (!TextureManager::Instance()->Load("../assets/scoreboard.png", "scoreboard"))
//    {
//        return false;
//    }
//
//    backgrounds[0] = std::make_unique<Background>(LoaderParams(0, 0, 432, 270, 2, "background"));
//    backgrounds[1] = std::make_unique<Background>(LoaderParams(864, 0, 432, 270, 2, "background"));
//    player = std::make_unique<Player>(LoaderParams(100, 100, 128, 55, 0.7f, "helicopter"));
//    ui.emplace_back(std::make_unique<Aim>(LoaderParams(0, 0, 11, 11, 3, "aim")));
//    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(0, 0, 360, 100, 1, "scoreboard")));
//    for (int i = 0; i < 8; i++)
//    {
//        animals.emplace_back(std::make_unique<Animal>(LoaderParams(i * 100, 400, 128, 82, "animal")));
//    }
//
//    SDL_ShowCursor(SDL_DISABLE);
//    Camera::Instance()->SetX(100);
//    Timer::Instance()->StartTimer();
//    projectiles = new ProjectileManager(*static_cast<Player*>(player.get()), missiles);
//
//    spawnDelay = 1600u;
//    nextSpawn = SDL_GetTicks() + spawnDelay;
//
//    std::cout << "entering PlayState\n";
//
//    return true;
//}
//
//bool PlayState::OnExit()
//{
//    backgrounds[0].reset();
//    backgrounds[1].reset();
//    player.reset();
//    enemies.clear();
//    animals.clear();
//    missiles.clear();
//    ui.clear();
//
//    TextureManager::Instance()->ClearFromTextureMap("background");
//    TextureManager::Instance()->ClearFromTextureMap("helicopter");
//    TextureManager::Instance()->ClearFromTextureMap("helicopter2");
//    TextureManager::Instance()->ClearFromTextureMap("animal");
//    TextureManager::Instance()->ClearFromTextureMap("missile");
//    TextureManager::Instance()->ClearFromTextureMap("explosion");
//    TextureManager::Instance()->ClearFromTextureMap("carrcass");
//    TextureManager::Instance()->ClearFromTextureMap("aim");
//
//    SDL_ShowCursor(SDL_ENABLE);
//    delete projectiles;
//
//    std::cout << "exiting PlayState\n";
//
//    return true;
//}
//
//void PlayState::CheckCollision()
//{
//    for (auto& m : missiles)
//    {
//        for (auto& e : enemies)
//        {
//            if (Collision::AABB(m.get(), e.get()))
//            {
//                Vector2D enemyPos = dynamic_cast<SDLGameObject*>(e.get())->GetPosition();
//                m->Destroy();
//                e->Destroy();
//                effects.emplace_back(std::make_unique<Explosion>(LoaderParams(int(enemyPos.GetX()), int(enemyPos.GetY()) - 16, 64, 64, 1.5f, "explosion")));
//                break;
//            }
//        }
//        for (auto& a : animals)
//        {
//            if (Collision::AABB(m.get(), a.get()))
//            {
//                Vector2D animalPos = dynamic_cast<SDLGameObject*>(a.get())->GetPosition();
//                m->Destroy();
//                a->Destroy();
//                effects.emplace_back(std::make_unique<Carrcass>(LoaderParams(int(animalPos.GetX()), int(animalPos.GetY()), 128, 82, 0.8f, "carrcass")));
//                break;
//            }
//        }
//    }
//
//    for (auto& e : enemies)
//    {
//        if (Collision::AABB(e.get(), player.get()))
//        {
//            e->Destroy();
//            player->Destroy();
//            Game::Instance()->GetStateMachine()->ChangeState(GameOverState::Instance());
//            return;
//        }
//        for (auto& a : animals)
//        {
//            if (Collision::AABB(e.get(), a.get()))
//            {
//                auto ani = dynamic_cast<Animal*>(a.get());
//                auto ene = dynamic_cast<Enemy*>(e.get());
//                if (ani->GetState() == FREE && ene->GetState() == HUNT)
//                {
//                    ani->HuntedBy(ene);
//                    ene->SetStateRun();
//                    ene->SetAnimal(ani);
//                    break;
//                }
//            }
//        }
//    }
//}
//
//void PlayState::Refresh()
//{
//    enemies.erase
//    (
//        std::remove_if(std::begin(enemies), std::end(enemies), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
//        std::end(enemies)
//    );
//    animals.erase
//    (
//        std::remove_if(std::begin(animals), std::end(animals), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
//        std::end(animals)
//    );
//    missiles.erase
//    (
//        std::remove_if(std::begin(missiles), std::end(missiles), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
//        std::end(missiles)
//    );
//    effects.erase
//    (
//        std::remove_if(std::begin(effects), std::end(effects), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
//        std::end(effects)
//    );
//}