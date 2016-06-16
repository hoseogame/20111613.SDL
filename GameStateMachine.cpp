#include "GameStateMachine.h"
#include "GameState.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
	std::list<GameState*>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); ++iter)
	{
		delete *iter;
		*iter = nullptr;
	}
	gameStates.clear();
}


void GameStateMachine::PushState(GameState* state)
{
	gameStates.push_back(state);
	gameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
	if (gameStates.empty() == true)
	{
		return;
	}

	gameStates.back()->OnExit();

	if(gameStates.size() < 2)
	{
		return;
	}

	delete gameStates.front();
	gameStates.pop_front();

	/*if (gameStates.back()->OnExit())
	{
		delete gameStates.front();
		gameStates.pop_front();
	}*/
}

void GameStateMachine::ChangeState(GameState* state)
{
	if (gameStates.empty() == true)
	{
		PushState(state);
		return;
	}

	if (gameStates.back()->GetStateID() == state->GetStateID())
	{
		return;
	}

	PopState();
	PushState(state);
}

void GameStateMachine::Update()
{
	if (gameStates.empty() == false)
	{
		gameStates.back()->Update();
	}
}

void GameStateMachine::Render()
{
	if (gameStates.empty() == false)
	{
		gameStates.back()->Render();
	}
}