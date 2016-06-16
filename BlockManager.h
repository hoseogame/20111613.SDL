#pragma once
#include "BlockInfo.h"
#include <list>
#include <SDL.h>


class Block;

class BlockManager
{
public:
	BlockManager(std::string _textureID);
	~BlockManager();

	void Init();
	void Draw();

	void MakeNewBlock();

	bool GetBeOngoingBlock() const { return beOngoingBlock; }
	void SetBeOngoingBlock(bool _beOngoing) { beOngoingBlock = _beOngoing; }	//юс╫ц
	Block* OngoingBlock() const
	{
		if (blocks.empty() == false)
		{
			return blocks.front();
		}
		return nullptr;
	}

private:
	Block* CreateBlock();

private:
	bool beOngoingBlock;
	std::list<Block*> blocks;
	static const char blockShape[SHAPE_COUNT][FIELD_WIDTH][FIELD_HEIGHT];

	std::string textureID;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};

