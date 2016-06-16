#pragma once
#include <list>

class GameState;

class GameStateMachine
{
public:
	GameStateMachine();
	~GameStateMachine();

	void ChangeState(GameState* state);
	void Update();
	void Render();

private:
	void PushState(GameState* state);
	void PopState();

private:
	std::list<GameState*> gameStates;
};

