#pragma once
#include <string>
#include <map>
#include <memory>

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
	std::unique_ptr<GameObject> Create(std::string typeID);

private:
	GameObjectFactory();
	GameObjectFactory(const GameObjectFactory& gof);

private:
	std::map<std::string, BaseCreator*> creators;
};

typedef GameObjectFactory TheGameObjectFactory;

