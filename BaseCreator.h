#pragma once
#include "GameObject.h"
#include <memory>

class BaseCreator
{
public:
	BaseCreator();
	virtual ~BaseCreator();

	virtual std::unique_ptr<GameObject> CreateGameObject() const = 0;
};

