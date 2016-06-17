#pragma once
#include "GameState.h"
#include <vector>
#include <memory>

class GameObject;
//class GameObjectFactory;

class MenuState : public GameState
{
public:
	MenuState();
	virtual ~MenuState();

	virtual void Update();
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const
	{
		return menuID;
	}

private:
	static void MenuToPlay();
	static void ExitFromMenu();

private:
	static const std::string menuID;

	//GameObjectFactory* gameObjectFactory;
	//std::vector<GameObject*> menuObjects;
	std::vector<std::unique_ptr<GameObject>> menuObjects;
};

