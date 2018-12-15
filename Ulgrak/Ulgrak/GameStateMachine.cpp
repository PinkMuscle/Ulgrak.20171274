#include "GameStateMachine.h"
#include "Camera.h"

void GameStateMachine::ChangeState(GameState *pState)
{
    if (pState != nullptr)
    {
        if (currentState != nullptr)
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
    if (currentState != nullptr)
        currentState->Update();
}

void GameStateMachine::Render()
{
    if (currentState != nullptr)
        currentState->Render();
}