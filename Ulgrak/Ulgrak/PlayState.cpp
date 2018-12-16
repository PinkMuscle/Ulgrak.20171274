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
#include "GunGenerator.h"
#include "Bullet.h"
#include "UIBox.h"
//Standard
#include <iostream>
#include <algorithm>

PlayState* PlayState::pInstance = nullptr;
const std::string PlayState::playID = "PLAY";

constexpr Uint32 spawnDelay = 9000u;

void PlayState::Update()
{
    int playerCount = 0;

    if (InputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
    {
        Game::Instance()->GetStateMachine()->ChangeState(PauseState::Instance());
        return;
    }
    if (SDL_GetTicks() > nextSpawn)
    {
        nextSpawn = SDL_GetTicks() + spawnDelay;

        int random = rand() % 4;
        switch (random)
        {
        case 0:
            effects.emplace_back(std::make_unique<GunGenerator>(LoaderParams(32, 20, 32, 32, 2, "gungenerator"), items));
            break;
        case 1:
            effects.emplace_back(std::make_unique<GunGenerator>(LoaderParams(32 + 384, 20, 32, 32, 2, "gungenerator"), items));
            break;
        case 2:
            effects.emplace_back(std::make_unique<GunGenerator>(LoaderParams(32, 20 - 256, 32, 32, 2, "gungenerator"), items));
            break;
        case 3:
            effects.emplace_back(std::make_unique<GunGenerator>(LoaderParams(32 + 384, 20 - 256, 32, 32, 2, "gungenerator"), items));
            break;
        default:
            break;
        }
    }

    background->Update();

    for (auto& objects : players)
    {
        if (objects->GetLife() == 0)
        {
            continue;
        }
        playerCount++;
        objects->Update();
    }
    if (!gameOver && playerCount <= 1)
    {
        gameOver = true;
        ui.emplace_back(std::make_unique<UIBox>(LoaderParams(120, 30, 100, 24, 6, "winner")));
    }

    for (auto& objects : items)
    {
        objects->Update();
    }
    for (auto& objects : projectiles)
    {
        objects->Update();
    }
    for (auto& objects : effects)
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
    for (auto& objects : items)
    {
        objects->Draw();
    }
    for (auto& objects : projectiles)
    {
        objects->Draw();
    }
    for (auto& objects : effects)
    {
        objects->Draw();
    }
    for (auto& objects : ui)
    {
        objects->Draw();
    }

    //¼ö¸í Ç¥½Ã
    TextPrinter::Instance()->Draw("x" + std::to_string(players[0]->GetLife()), 295, 495, 2);
    TextPrinter::Instance()->Draw("x" + std::to_string(players[1]->GetLife()), 864 - 200 - 30 * 4 + 95, 495, 2);
    //ÃÑ¾Ë ¼ö Ç¥½Ã
    if (players[0]->GetMagazine() == -1)
    {
        TextPrinter::Instance()->Draw("in", 295, 520, 2);
    }
    else
    {
        TextPrinter::Instance()->Draw("x" + std::to_string(players[0]->GetMagazine()), 295, 520, 2);
    }
    if (players[1]->GetMagazine() == -1)
    {
        TextPrinter::Instance()->Draw("in", 864 - 200 - 30 * 4 + 95, 520, 2);
    }
    else
    {
        TextPrinter::Instance()->Draw("x" + std::to_string(players[1]->GetMagazine()), 864 - 200 - 30 * 4 + 95, 520, 2);
    }
}

bool PlayState::OnEnter()
{
    if (!TextureManager::Instance()->Load("Assets/background.png", "background"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player1.png", "player1"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player2.png", "player2"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player3.png", "player3"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/platform.png", "platform"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/halfplatform.png", "halfplatform"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/gungenerator.png", "gungenerator"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/gun0.png", "gun0"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/gun1.png", "gun1"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/bullet.png", "bullet"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/bullet_purple.png", "bullet_purple"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/status.png", "status"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player1_icon.png", "player1_icon"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player2_icon.png", "player2_icon"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/player3_icon.png", "player3_icon"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/life_icon.png", "life_icon"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/bullet_icon.png", "bullet_icon"))
    {
        return false;
    }
    if (!TextureManager::Instance()->Load("Assets/winner.png", "winner"))
    {
        return false;
    }

    //¹è°æ
    background = std::make_unique<Background>(LoaderParams(-1296 + 256, -810, 1728, 1080, 1.5f, "background"));
    //ÇÃ·¹ÀÌ¾î
    players.emplace_back(std::make_unique<Player>(LoaderParams(100, 20 - 128, 32, 32, "player1", "1P"), platforms, projectiles));
    players.emplace_back(std::make_unique<Player>(LoaderParams(400, 20 - 128, 32, 32, "player2", "2P"), platforms, projectiles));
    //1Ãþ ÇÃ·§Æû
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(0, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(128, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(256, 100, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(384, 100, 32, 8, 4, "platform")));
    //2Ãþ ÇÃ·§Æû
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(64, 100 - 128, 31, 4, 4, "halfplatform", "HALF")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(320, 100 - 128, 31, 4, 4, "halfplatform", "HALF")));
    //3Ãþ ÇÃ·§Æû
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(0, 100 - 256, 32, 8, 4, "platform")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(128, 100 - 256, 31, 4, 4, "halfplatform", "HALF")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(256, 100 - 256, 31, 4, 4, "halfplatform", "HALF")));
    platforms.emplace_back(std::make_unique<Platform>(LoaderParams(384, 100 - 256, 32, 8, 4, "platform")));
    //UI
    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(200, 480, 32, 30, 4, "status")));
    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(864 - 200 - 30 * 4, 480, 32, 30, 4, "status")));

    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(200, 480, 22, 25, 3, "player1_icon")));
    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(864 - 200 - 30 * 4, 480, 22, 25, 3, "player2_icon")));

    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(270, 494, 7, 6, 3, "life_icon")));
    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(864 - 200 - 30 * 4 + 70, 494, 7, 6, 3, "life_icon")));

    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(270, 519, 7, 6, 3, "bullet_icon")));
    ui.emplace_back(std::make_unique<UIBox>(LoaderParams(864 - 200 - 30 * 4 + 70, 519, 7, 6, 3, "bullet_icon")));

    nextSpawn = SDL_GetTicks() + spawnDelay - 5000u;
    gameOver = false;
    Camera::Instance()->Init();

    std::cout << "entering PlayState\n";

    return true;
}

bool PlayState::OnExit()
{
    background.reset();
    platforms.clear();
    players.clear();
    items.clear();
    projectiles.clear();
    effects.clear();
    ui.clear();

    TextureManager::Instance()->ClearFromTextureMap("background");
    TextureManager::Instance()->ClearFromTextureMap("player1");
    TextureManager::Instance()->ClearFromTextureMap("player2");
    TextureManager::Instance()->ClearFromTextureMap("player3");
    TextureManager::Instance()->ClearFromTextureMap("platform");
    TextureManager::Instance()->ClearFromTextureMap("halfplatform");
    TextureManager::Instance()->ClearFromTextureMap("gungenerator");
    TextureManager::Instance()->ClearFromTextureMap("gun0");
    TextureManager::Instance()->ClearFromTextureMap("gun1");
    TextureManager::Instance()->ClearFromTextureMap("bullet");
    TextureManager::Instance()->ClearFromTextureMap("bullet_purple");
    TextureManager::Instance()->ClearFromTextureMap("status");
    TextureManager::Instance()->ClearFromTextureMap("player1_icon");
    TextureManager::Instance()->ClearFromTextureMap("player2_icon");
    TextureManager::Instance()->ClearFromTextureMap("player3_icon");
    TextureManager::Instance()->ClearFromTextureMap("life_icon");
    TextureManager::Instance()->ClearFromTextureMap("bullet_icon");
    TextureManager::Instance()->ClearFromTextureMap("winner");

    std::cout << "exiting PlayState\n";

    return true;
}

void PlayState::CheckCollision()
{
    for (auto& p : players)
    {
        for (auto& i : items)
        {
            if (Collision::AABB(p.get(), i.get()))
            {
                if (i->IsActive())
                {
                    p->ChangeGun(i->GetTag());
                    i->Destroy();
                }
            }
        }
        for (auto& proj : projectiles)
        {
            if (Collision::AABB(p.get(), proj.get()))
            {
                if (p->GetTag() != proj->GetTag())
                {
                    if (proj->GetVelocity().x > 0)
                    {
                        p->Damaged(dynamic_cast<Bullet*>(proj.get())->GetDamage());
                    }
                    else
                    {
                        p->Damaged(dynamic_cast<Bullet*>(proj.get())->GetDamage() * -1);
                    }
                    proj->Destroy();
                }
            }
        }
    }
}

void PlayState::Refresh()
{
    items.erase
    (
        std::remove_if(std::begin(items), std::end(items), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
        std::end(items)
    );
    projectiles.erase
    (
        std::remove_if(std::begin(projectiles), std::end(projectiles), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
        std::end(projectiles)
    );
    effects.erase
    (
        std::remove_if(std::begin(effects), std::end(effects), [](const std::unique_ptr<GameObject> &object) {return !object->IsActive(); }),
        std::end(effects)
    );
}