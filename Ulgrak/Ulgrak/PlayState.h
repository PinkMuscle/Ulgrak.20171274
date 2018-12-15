#ifndef PlayState_h
#define PlayState_h
#include "GameState.h"
#include <vector>
#include <array>
#include <memory>

class PlayState : public GameState
{
public:
    ~PlayState() {}
    static PlayState* Instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new PlayState();
        }
        return pInstance;
    }
    virtual void Update();
    virtual void Render();
    virtual bool OnEnter();
    virtual bool OnExit();
    void CheckCollision();
    void Refresh();
    virtual std::string GetStateID() const { return playID; }

private:
    PlayState() {}
    static PlayState* pInstance;
    static const std::string playID;
    Uint32 nextSpawn;

    std::unique_ptr<GameObject> background;
    std::vector<std::unique_ptr<GameObject>> platforms;
    std::vector<std::unique_ptr<GameObject>> players;
    std::vector<std::unique_ptr<GameObject>> items;
    std::vector<std::unique_ptr<GameObject>> projectiles;
    std::vector<std::unique_ptr<GameObject>> effects;
    std::vector<std::unique_ptr<GameObject>> ui;
};

#endif