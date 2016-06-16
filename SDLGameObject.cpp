#include "SDLGameObject.h"
#include "LoaderParams.h"
#include "TextureManager.h"
#include "Game.h"

SDLGameObject::SDLGameObject()
{
}


SDLGameObject::~SDLGameObject()
{
}


void SDLGameObject::Draw()
{
	TheTextureManager::Instance()->DrawFrame(textureID, x, y, width, height, currentRow, currentFrame,
		TheGame::Instance()->GetRenderer());
}

void SDLGameObject::Update()
{
	
}

void SDLGameObject::Clean()
{

}

void SDLGameObject::Load(const LoaderParams* params)
{
	x = params->GetX();
	y = params->GetY();
	width = params->GetWidth();
	height = params->GetHeight();
	textureID = params->GetTextureID();
	currentRow = 1;
	currentFrame = 1;
}