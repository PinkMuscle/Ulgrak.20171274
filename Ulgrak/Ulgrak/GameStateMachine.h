#ifndef GameStateMachine_h
#define GameStateMachine_h
#include "GameState.h"
#include <vector>

class GameStateMachine
{
public:
    void ChangeState(GameState* pState);
    void PushState(GameState* pState);
    void PopState();

    virtual void Update();
    virtual void Render();

private:
    GameState* currentState;
    GameState* prevState;
    std::vector<GameState*> gameStates;
};

#endif