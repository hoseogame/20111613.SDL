#include "StateParser.h"
#include "TextureManager.h"
#include "Game.h"
#include "GameObjectFactory.h"
#include "GameObject.h"
#include "LoaderParams.h"
#include <iostream>


StateParser::StateParser()
{
}


StateParser::~StateParser()
{
}

bool StateParser::ParseState(const char* stateFile, std::string stateID
	, std::vector<GameObject*>* objects, std::vector<std::string>* textureIDs)
{
	TiXmlDocument xmlDoc;
	if(xmlDoc.LoadFile(stateFile) == false)
	{
		std::cerr << xmlDoc.ErrorDesc() << std::endl;
		return false;
	}

	TiXmlElement* root = xmlDoc.RootElement();

	TiXmlElement* stateRoot = 0;
	for (TiXmlElement* element = root->FirstChildElement(); 
	element != NULL; element = element->NextSiblingElement())
	{
		if (element->Value() == stateID)
		{
			stateRoot = element;
		}
	}

	TiXmlElement* textureRoot = 0;
	for (TiXmlElement* element = stateRoot->FirstChildElement();
	element != NULL; element = element->NextSiblingElement())
	{
		if (element->Value() == std::string("TEXTURES"))
		{
			textureRoot = element;
		}
	}
	ParseTextures(textureRoot, textureIDs);

	TiXmlElement* objectRoot = 0;
	for (TiXmlElement* element = stateRoot->FirstChildElement();
	element != NULL; element = element->NextSiblingElement())
	{
		if (element->Value() == std::string("OBJECTS"))
		{
			objectRoot = element;
		}
	}
	ParseObjects(objectRoot, objects);

	return true;
}

void StateParser::ParseObjects(TiXmlElement* stateRoot, std::vector<GameObject*>* objects)
{
	for (TiXmlElement* e = stateRoot->FirstChildElement();
	e != NULL; e = e->NextSiblingElement())
	{
		int x, y, width, height, numFrames, callbackID, animSpeed;
		std::string textureID;
		e->Attribute("x", &x);
		e->Attribute("y", &y);
		e->Attribute("width", &width);
		e->Attribute("height", &height);
		e->Attribute("numFrames", &numFrames);
		e->Attribute("callbackID", &callbackID);
		e->Attribute("animSpeed", &animSpeed);
		textureID = e->Attribute("textureID");
		GameObject* gameObject = TheGameObjectFactory::Instance()->Create(e->Attribute("type"));
		LoaderParams load(x, y, width, height, textureID);
		gameObject->Load(&load);
		//gameObject->Load(new LoaderParams(x, y, width, height, textureID));
		objects->push_back(gameObject);
	}
}

void StateParser::ParseTextures(TiXmlElement* stateRoot, std::vector<std::string>* textureIDs)
{
	for (TiXmlElement* element = stateRoot->FirstChildElement();
	element != NULL; element = element->NextSiblingElement())
	{
		std::string fileNameAttribute = element->Attribute("filename");
		std::string idAttribute = element->Attribute("ID");
		textureIDs->push_back(idAttribute);
		
		TheTextureManager::Instance()->Load(fileNameAttribute,
			idAttribute, TheGame::Instance()->GetRenderer());
	}
}