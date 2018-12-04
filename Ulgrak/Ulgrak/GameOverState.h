#ifndef GameOverState_h
#define GameOverState_h
#include "GameState.h"

class GameOverState : public GameState
{
public:
    ~GameOverState() {}
    static GameOverState* Instance()
    {
        if (pInstance == nullptr)
        {
            pInstance = new GameOverState();
        }
        return pInstance;
    }
    virtual bool OnEnter();
    virtual bool OnExit();
    virtual std::string GetStateID() const { return gameOverID; }

private:
    GameOverState() {}
    static GameOverState* pInstance;
    static const std::string gameOverID;
    static void GameOverToMain();
    static void RestartPlay();
};

#endif