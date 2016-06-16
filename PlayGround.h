#pragma once
#include "SDLGameObject.h"
#include "BlockInfo.h"
#include "BaseCreator.h"
#include <SDL.h>
#include <vector>



class BlockManager;
class GroundBlockManager;

class PlayGround : public SDLGameObject
{
public:
	PlayGround();
	~PlayGround();

	void Init();
	virtual void Draw();
	virtual void Update();
	virtual void Clean();
	virtual void Load(const LoaderParams* params);

private:
	BlockManager* blockManager;
	GroundBlockManager* groundBlockManager;

	bool firstPress[3];
	SDL_Surface* surfaceMessage;
};

class PlayGroundCreator : public BaseCreator
{
public:
	virtual GameObject* CreateGameObject() const
	{
		return new PlayGround();
	}
};