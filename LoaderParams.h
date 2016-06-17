#pragma once
#include <string>

class LoaderParams
{
public:
	LoaderParams(int _x, int _y, int _width, int _height, std::string _textureID)
		: x(_x), y(_y), width(_width), height(_height), textureID(_textureID)
	{}

	int GetX() const { return x; }
	int GetY() const { return y; }
	int GetWidth() const { return width; }
	int GetHeight() const { return height; }
	std::string GetTextureID() const { return textureID; }

private:
	int x;
	int y;
	int width;
	int height;
	std::string textureID;
};
