#pragma once
#include <map>
#include <SDL.h>

class TextureManager
{
public:
	static TextureManager* Instance()
	{
		static TextureManager* instance = nullptr;
		if (instance == nullptr)
		{
			instance = new TextureManager();
		}
		return instance;
	}

	~TextureManager();

	bool Load(std::string _fileName, std::string _id, SDL_Renderer* _renderer);
	void Draw(std::string _id, int _x, int _y, int _width, int _height, SDL_Renderer* _renderer, SDL_RendererFlip _flip = SDL_FLIP_NONE);
	void DrawFrame(std::string _id, int _x, int _y, int _width, int _height, int _currentRow, int _currentFrame
		, SDL_Renderer* _renderer, SDL_RendererFlip _flip = SDL_FLIP_NONE);
	void DrawStoD(std::string _id, SDL_Rect const& source, SDL_Rect const& dest, 
		SDL_Renderer* _renderer, SDL_RendererFlip _flip = SDL_FLIP_NONE);

	void ClearFromTextureMap(std::string _id)
	{
		SDL_DestroyTexture(textureMap[_id]);
		textureMap.erase(_id);
	}

private:
	TextureManager();
	TextureManager(const TextureManager& tm);

private:
	std::map<std::string, SDL_Texture*> textureMap;
};

typedef TextureManager TheTextureManager;