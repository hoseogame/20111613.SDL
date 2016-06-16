#pragma once
#include "GameObject.h"

class BaseCreator
{
public:
	BaseCreator();
	virtual ~BaseCreator();

	virtual GameObject* CreateGameObject() const = 0;
};

