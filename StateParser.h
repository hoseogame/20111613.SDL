#pragma once
#include "tinyxml.h"
#include <vector>
#include <memory>

class GameObject;

class StateParser
{
public:
	StateParser();
	~StateParser();

	bool ParseState(const char* stateFile, std::string stateID
		, std::vector<std::unique_ptr<GameObject>>* objects, std::vector<std::string>* textureIDs);

private:
	void ParseObjects(TiXmlElement* stateRoot, std::vector<std::unique_ptr<GameObject>>* objects);
	void ParseTextures(TiXmlElement* stateRoot, std::vector<std::string>* textureIDs);
};

