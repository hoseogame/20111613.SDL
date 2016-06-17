#pragma once
#include "SDLGameObject.h"
#include "BaseCreator.h"
#include <memory>

class LoaderParams;
class MenuState;

enum button_state
{
	
	MOUSE_OUT,
	MOUSE_OVER,
	CLICKED
};

using Callback = void(*)();

class MenuButton : public SDLGameObject
{
public:
	MenuButton();
	~MenuButton();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();

	void SetCallback(const Callback _callback)
	{
		callback = _callback;
	}

private:
	bool released;
	Callback callback;
};

class MenuButtonCreator : public BaseCreator
{
public:
	virtual std::unique_ptr<GameObject> CreateGameObject() const
	{
		//return new MenuButton();
		return std::unique_ptr<GameObject>(new MenuButton());
	}
};