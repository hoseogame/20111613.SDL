#pragma once
#include <string>
#include <map>

class BaseCreator;
class GameObject;

class GameObjectFactory
{
public:
	~GameObjectFactory();

	static GameObjectFactory* Instance()
	{
		static GameObjectFactory* gameObjectFactory = nullptr;
		if (gameObjectFactory == nullptr)
		{
			gameObjectFactory = new GameObjectFactory();
		}
		return gameObjectFactory;
	}

	bool RegisterType(std::string typeID, BaseCreator* creator);
	GameObject* Create(std::string typeID);

private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory& gof);

private:
	std::map<std::string, BaseCreator*> creators;
};

typedef GameObjectFactory TheGameObjectFactory;

