#include "MenuState.h"
#include "TextureManager.h"
#include "Game.h"
#include "LoaderParams.h"
#include "MenuButton.h"
#include "GameStateMachine.h"
#include "PlayState.h"
#include "GameObjectFactory.h"
#include "StateParser.h"

const std::string MenuState::menuID = "MENU";

MenuState::MenuState() : GameState()
{
	//gameObjectFactory = new GameObjectFactory();
}


MenuState::~MenuState()
{
	/*if (gameObjectFactory != nullptr)
	{
		delete gameObjectFactory;
		gameObjectFactory = nullptr;
	}*/

	/*for (size_t i = 0; i < menuObjects.size(); ++i)
	{
		menuObjects[i]->Clean();
		delete menuObjects[i];
		menuObjects[i] = nullptr;
	}
	menuObjects.clear();*/

	menuObjects.clear();
}

void MenuState::Update()
{
	for (size_t i = 0; i < menuObjects.size(); ++i)
	{
		menuObjects[i]->Update();
	}
}

void MenuState::Render()
{
	for (size_t i = 0; i < menuObjects.size(); ++i)
	{
		menuObjects[i]->Draw();
	}
}

bool MenuState::OnEnter()
{
	StateParser stateParser;
	stateParser.ParseState("GameInfo.xml", menuID, &menuObjects, &textureIDList);
	
	//callback setting 추후 변경할 것


	GameObject* gameObject = menuObjects[0].release();
	dynamic_cast<MenuButton*>(gameObject)->SetCallback(MenuToPlay);
	menuObjects[0].reset(gameObject);

	gameObject = menuObjects[1].release();
	dynamic_cast<MenuButton*>(gameObject)->SetCallback(ExitFromMenu);
	menuObjects[1].reset(gameObject);


	//dynamic_cast<MenuButton*>(menuObjects[0])->SetCallback(MenuToPlay);
	//dynamic_cast<MenuButton*>(menuObjects[1])->SetCallback(ExitFromMenu);

	//-------------------------------------------------------------2
	/*if (TheTextureManager::Instance()->Load("assets/play.png", "playbutton",
		TheGame::Instance()->GetRenderer()) == false)
	{
		return false;
	}

	if (TheTextureManager::Instance()->Load("assets/exit.png", "exitbutton",
		TheGame::Instance()->GetRenderer()) == false)
	{
		return false;
	}

	gameObjectFactory->RegisterType("MenuButton", new MenuButtonCreator());
	GameObject* obj = gameObjectFactory->Create("MenuButton");
	obj->Load(new LoaderParams(50, 150, 400, 100, "playbutton"));
	dynamic_cast<MenuButton*>(obj)->SetCallback(MenuToPlay);
	menuObjects.push_back(obj);

	obj = gameObjectFactory->Create("MenuButton");
	obj->Load(new LoaderParams(50, 300, 400, 100, "exitbutton"));
	dynamic_cast<MenuButton*>(obj)->SetCallback(ExitFromMenu);
	menuObjects.push_back(obj);*/

	//-------------------------------------------------------------1
	/*obj = new MenuButton(MenuToPlay);
	menuObjects.push_back(obj);
	menuObjects.back()->Load(new LoaderParams(50, 150, 400, 100, "playbutton"));
	obj = new MenuButton(ExitFromMenu);
	menuObjects.push_back(obj);
	menuObjects.back()->Load(new LoaderParams(50, 300, 400, 100, "exitbutton"));*/

	return true;
}

bool MenuState::OnExit()
{
	//TheTextureManager::Instance()->ClearFromTextureMap("playbutton");
	//TheTextureManager::Instance()->ClearFromTextureMap("exitbutton");

	for (size_t i = 0; i < textureIDList.size(); ++i)
	{
		TheTextureManager::Instance()->ClearFromTextureMap(textureIDList[i]);
	}

	for (size_t i = 0; i < menuObjects.size(); ++i)
	{
		menuObjects[i]->Clean();
		//얻는 효과는 밑에 두 줄 제거
		//delete menuObjects[i];
		//menuObjects[i] = nullptr;
	}
	//menuObjects.clear();

	return true;
}

void MenuState::MenuToPlay()
{
	TheGame::Instance()->GetGameStateMachine()->ChangeState(new PlayState());
}

void MenuState::ExitFromMenu()
{
	TheGame::Instance()->Quit();
}
