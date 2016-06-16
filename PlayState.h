#pragma once
#include "GameState.h"
#include <vector>

//class PlayGround;
class GameObject;
//class GameObjectFactory;

class PlayState : public GameState
{
public:
	PlayState();
	virtual ~PlayState();

	virtual void Update();
	virtual void Render();
	virtual bool OnEnter();
	virtual bool OnExit();

	virtual std::string GetStateID() const
	{
		return playID;
	}

private:
	static const std::string playID;
	
	//GameObjectFactory* gameObjectFactory;
	//GameObject* gameObject;
	std::vector<GameObject*> playObjects;
};

