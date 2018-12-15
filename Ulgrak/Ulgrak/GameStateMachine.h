#ifndef GameStateMachine_h
#define GameStateMachine_h
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
    void ChangeState(GameState* pState);
    void PopState();
	GameState* GetCurrentState() { return currentState; }

    virtual void Update();
    virtual void Render();

private:
    GameState* currentState = nullptr;
    GameState* prevState = nullptr;
};

#endif