#include "GameStateMachine.h"
#include "GameState.h"


GameStateMachine::GameStateMachine()
{
}


GameStateMachine::~GameStateMachine()
{
	std::list<std::unique_ptr<GameState>>::iterator iter;
	for (iter = gameStates.begin(); iter != gameStates.end(); ++iter)
	{
		//delete *iter;
		//*iter = nullptr;
	}
	gameStates.clear();
}


void GameStateMachine::PushState(GameState* state)
{
	gameStates.push_back(std::unique_ptr<GameState>(state));
	gameStates.back()->OnEnter();
}

void GameStateMachine::PopState()
{
	/*if(gameStates.size() < 2)
	{
	return;
	}*/

	if (gameStates.empty() == true)
	{
		return;
	}

	gameStates.back()->OnExit();

	//딜리트 하지 않는다.
//	delete gameStates.front();
//	gameStates.pop_front();
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

	if(gameStates.size() > 1)
	{
		gameStates.pop_front();
	}
}

void GameStateMachine::Render()
{
	if (gameStates.empty() == false)
	{
		gameStates.back()->Render();
	}
}