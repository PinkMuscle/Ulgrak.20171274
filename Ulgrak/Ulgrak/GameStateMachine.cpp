#include "GameStateMachine.h"

void GameStateMachine::ChangeState(GameState *pState)
{
    if (pState != NULL)
    {
        if (currentState != NULL)
        {
            prevState = currentState;
            currentState->OnExit();
        }
        currentState = pState;
        currentState->OnEnter();
    }
}

void GameStateMachine::PopState()
{
    ChangeState(prevState);
}

void GameStateMachine::Update()
{
    if (currentState != NULL)
        currentState->Update();
}

void GameStateMachine::Render()
{
    if (currentState != NULL)
        currentState->Render();
}