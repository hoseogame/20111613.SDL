#include "GameObjectFactory.h"
#include "BaseCreator.h"


GameObjectFactory::GameObjectFactory()
{
}


GameObjectFactory::~GameObjectFactory()
{
	//creators 비워주기
	std::map<std::string, BaseCreator*>::iterator iter
		= creators.begin();
	while (iter != creators.end())
	{
		creators.erase(iter++);
	}
}

bool GameObjectFactory::RegisterType(std::string typeID, BaseCreator* creator)
{
	std::map<std::string, BaseCreator*>::iterator iter
		= creators.find(typeID);

	if (iter != creators.end())
	{
		delete creator;
		creator = nullptr;
		return false;
	}

	creators[typeID] = creator;
	return true;
}

GameObject* GameObjectFactory::Create(std::string typeID)
{
	std::map<std::string, BaseCreator*>::iterator iter
		= creators.find(typeID);

	if (iter == creators.end())
	{
		return nullptr;
	}

	BaseCreator* creator = (*iter).second;
	return creator->CreateGameObject();
}