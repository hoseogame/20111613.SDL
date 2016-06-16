#pragma once
#include "BlockInfo.h"
#include <SDL.h>
#include <string>
#include <list>

struct GroundBlock;
class Block;

class GroundBlockManager;
using TranslateEvent = bool(GroundBlockManager::*)(Block* const);

class GroundBlockManager
{
public:
	GroundBlockManager(std::string _textureID);
	~GroundBlockManager();

	void Init();
	void Draw();
	//Block의 행동에 맞춰 Ground정보 변화
	bool TranslateBlock(Block* const block, block_behavior const behavior);
	void CheckFullLine();
	void EraseFullLine(Block* const block);
	bool ProcessFullLine();

private:
	bool StrikeCheck(Block* const block, int add_x = 0, int add_y = 0, int add_angle = 0);
	void EraseBlockOfScreen(Block* const block);
	void ShowBlockOfScreen(Block* const block);

	bool DownMoveBlock(Block* const block);
	bool LeftMoveBlock(Block* const block);
	bool RightMoveBlock(Block* const block);
	bool RotateBlock(Block* const block);

private:
	GroundBlock** groundBlock;
	std::list<SDL_Point> destructionBlocks;
	bool* completeDestruction;
	static const char blockShape[SHAPE_COUNT][ANGLE_COUNT][FIELD_WIDTH][FIELD_HEIGHT];

	std::string textureID;
	SDL_Rect srcRect;
	SDL_Rect destRect;
};