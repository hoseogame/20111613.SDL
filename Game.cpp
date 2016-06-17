#include "Game.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "PlayState.h"
#include "InputHandler.h"
#include "GameObjectFactory.h"
#include "TextureManager.h"
#include "MenuButton.h"
#include "PlayGround.h"

Game::Game() : gameStateMachine(nullptr)
{
}


Game::~Game()
{
	if (gameStateMachine != nullptr)
	{
		delete gameStateMachine;
		gameStateMachine = nullptr;
	}
}


bool Game::Init(const char* _title, int _x, int _y, int _width, int _height, int _flags)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) >= 0)
	{
		pWindow = SDL_CreateWindow(_title, _x, _y, _width, _height, _flags);
		if (pWindow != 0)
		{
			renderer = SDL_CreateRenderer(pWindow, -1, 0);
			//SDL_RENDERER_ACCELERATED
		}
	}
	else 
	{
		return false;
	}

	runningCheck = true;

	TheGameObjectFactory::Instance()->RegisterType("MenuButton", new MenuButtonCreator());
	TheGameObjectFactory::Instance()->RegisterType("PlayGround", new PlayGroundCreator());

	gameStateMachine = new GameStateMachine();
	//gameStateMachine->ChangeState(new PlayState());
	gameStateMachine->ChangeState(new MenuState());
	frameTime = 0;

	return true;
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
	SDL_RenderClear(renderer);
	///////////////////////////////////////////////////////
	gameStateMachine->Render();


	///////////////////////////////////////////////////////
	SDL_RenderPresent(renderer);
}

void Game::Update()
{
	gameStateMachine->Update();
}

void Game::HandleEvents()
{
	TheInputHandler::Instance()->Update();
}

void Game::Clean()
{
	delete TheGameObjectFactory::Instance();
	delete TheInputHandler::Instance();
	delete TheTextureManager::Instance();

	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(pWindow);
	SDL_Quit();
}