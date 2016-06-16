#pragma once
#include <SDL.h>

class GameStateMachine;

class Game
{
public:
	static Game* Instance()
	{
		static Game* instance = nullptr;
		if (instance == nullptr)
		{
			instance = new Game();
		}
		return instance;
	}

	~Game();

	bool Init(const char* _title, int _x, int _y, int _width, int _height, int _flags);
	void Render();
	void Update();
	void HandleEvents();
	void Clean();
	bool Running() const { return runningCheck; }
	void Quit() { runningCheck = false; }

	SDL_Renderer* GetRenderer() const { return renderer; }
	GameStateMachine* GetGameStateMachine() const { return gameStateMachine; }

	void SetFrameTime(Uint32 _frameTime) { frameTime = _frameTime; }
	Uint32 GetFrameTime() const { return frameTime; }

private:
	Game();
	Game(const Game& game);

private:

	SDL_Window* pWindow;
	SDL_Renderer* renderer;
	bool runningCheck;

	GameStateMachine* gameStateMachine;
	Uint32 frameTime;
};

typedef Game TheGame;