#include "PlayState.h"
#include "Game.h"
#include "TextureManager.h"
#include "PlayGround.h"
#include "LoaderParams.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
#include "GameObjectFactory.h"
#include "StateParser.h"

const std::string PlayState::playID = "PLAY";

PlayState::PlayState() : GameState()
{
	//gameObjectFactory = new GameObjectFactory();
}


PlayState::~PlayState()
{
	/*if (gameObjectFactory != nullptr)
	{
		delete gameObjectFactory;
		gameObjectFactory = nullptr;
	}*/
}


void PlayState::Update()
{
	if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_ESCAPE))
	{
		TheGame::Instance()->GetGameStateMachine()->ChangeState(new MenuState());
		return;
	}

	for (size_t i = 0; i < playObjects.size(); ++i)
	{
		playObjects[i]->Update();
	}
}

void PlayState::Render()
{
	for (size_t i = 0; i < playObjects.size(); ++i)
	{
		playObjects[i]->Draw();
	}
}

bool PlayState::OnEnter()
{
	//TheTextureManager::Instance()->Load("assets/tile.png", "tile", TheGame::Instance()->GetRenderer());

	//gameObjectFactory->RegisterType("PlayGround", new PlayGroundCreator());
	//gameObject = gameObjectFactory->Create("PlayGround");
	//gameObject->Load(new LoaderParams(START_GROUND_X, START_GROUND_Y, BLOCK_SIZE, BLOCK_SIZE, "tile"));

	StateParser stateParser;
	stateParser.ParseState("GameInfo.xml", playID, &playObjects, &textureIDList);

	return true;
}

bool PlayState::OnExit()
{
	for (size_t i = 0; i < textureIDList.size(); ++i)
	{
		TheTextureManager::Instance()->ClearFromTextureMap(textureIDList[i]);
	}

	for (size_t i = 0; i < playObjects.size(); ++i)
	{
		playObjects[i]->Clean();
		delete playObjects[i];
		playObjects[i] = nullptr;
	}
	playObjects.clear();

	return true;
}