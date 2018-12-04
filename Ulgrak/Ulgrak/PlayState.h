#ifndef PlayState_h
#define PlayState_h
#include "GameState.h"

class SDLGameObject;

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
    virtual bool OnEnter();
    virtual bool OnExit();
    virtual std::string GetStateID() const { return playID; }

private:
    PlayState() {}
    static PlayState* pInstance;
    static const std::string playID;

    bool CheckCollision(SDLGameObject* p1, SDLGameObject* p2);
};

#endif