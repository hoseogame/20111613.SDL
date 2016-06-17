#include "TextureManager.h"
#include <SDL_image.h>


TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

bool TextureManager::Load(std::string _fileName, std::string _id, SDL_Renderer* _renderer)
{
	SDL_Surface* tempSurface = IMG_Load(_fileName.c_str());
	if (tempSurface == 0)
	{
		return false;
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(_renderer, tempSurface);
	SDL_FreeSurface(tempSurface);
	if (texture != 0)
	{
		textureMap[_id] = texture;
		return true;
	}

	return false;
}

void TextureManager::Draw(std::string _id, int _x, int _y, int _width, int _height, SDL_Renderer* _renderer, SDL_RendererFlip _flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = destRect.w = _width;
	srcRect.h = destRect.h = _height;
	destRect.x = _x;
	destRect.y = _y;

	SDL_RenderCopyEx(_renderer, textureMap[_id], &srcRect, &destRect, 0, 0, _flip);
}

void TextureManager::DrawFrame(std::string _id, int _x, int _y, int _width, int _height, int _currentRow, int _currentFrame
	, SDL_Renderer* _renderer, SDL_RendererFlip _flip)
{
	SDL_Rect srcRect;
	SDL_Rect destRect;
	srcRect.x = _width * (_currentFrame);
	srcRect.y = _height * (_currentRow - 1);
	srcRect.w = destRect.w = _width;
	srcRect.h = destRect.h = _height;
	destRect.x = _x;
	destRect.y = _y;

	SDL_RenderCopyEx(_renderer, textureMap[_id], &srcRect, &destRect, 0, 0, _flip);
}

void TextureManager::DrawStoD(std::string _id, SDL_Rect const& source, SDL_Rect const& dest,
	SDL_Renderer* _renderer, SDL_RendererFlip _flip)
{
	SDL_RenderCopyEx(_renderer, textureMap[_id], &source, &dest, 0, 0, _flip);
}