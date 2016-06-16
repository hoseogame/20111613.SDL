#pragma once
#include "GameObject.h"
#include <string>

class SDLGameObject : public GameObject
{
public:
	SDLGameObject();
	virtual ~SDLGameObject();

	virtual void Draw();
	virtual void Update();
	virtual void Clean();
	virtual void Load(const LoaderParams* params);

protected:
	int x;
	int y;
	int width;
	int height;
	int currentRow;
	int currentFrame;
	std::string textureID;
};

