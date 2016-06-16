#include "BlockManager.h"
#include "BlockInfo.h"
#include "Game.h"
#include "TextureManager.h"
#include <time.h>

const char BlockManager::blockShape[SHAPE_COUNT][FIELD_WIDTH][FIELD_HEIGHT] = 
{
	//막대모양
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,
	//네모모양
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,
	//'ㅓ' 모양
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,
	//'ㄱ'모양
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,
	//'ㄴ' 모양
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,
	//'Z' 모양
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,
	//'S' 모양
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,
};


BlockManager::BlockManager(std::string _textureID)
	:beOngoingBlock(false), textureID(_textureID)
{
	srand((unsigned)time(NULL));

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = IMG_SIZE;
	srcRect.h = IMG_SIZE;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = BLOCK_SIZE;
	destRect.h = BLOCK_SIZE;
}


BlockManager::~BlockManager()
{
	std::list <Block*>::iterator iter;
	for (iter = blocks.begin(); iter != blocks.end(); ++iter)
	{
		delete (*iter);
		*iter = nullptr;
	}
	blocks.clear();
}

void BlockManager::Init()
{
	blocks.push_back(CreateBlock());	//current block
	blocks.push_back(CreateBlock());	//preview block
}

void BlockManager::Draw()
{
	srcRect.x = blocks.back()->GetColor() * IMG_SIZE;

	for (int i = 0; i < FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < FIELD_WIDTH; ++j)
		{
			if (blockShape[blocks.back()->GetShape()][i][j] == 0)
			{
				continue;
			}

			destRect.x = 370 + ground_size::BLOCK_SIZE * j;
			destRect.y = 50 + ground_size::BLOCK_SIZE * i;

			TheTextureManager::Instance()->DrawStoD(textureID, srcRect, destRect, TheGame::Instance()->GetRenderer());
		}
	}
}

void BlockManager::MakeNewBlock()
{
	if (beOngoingBlock == true)
	{
		return;
	}

	blocks.pop_front();
	blocks.push_back(CreateBlock());

	beOngoingBlock = true;
}

Block* BlockManager::CreateBlock()
{
	int shape = 0;
	int i = rand() % 100;
	if (i <= 10)		//막대기 나올확률 계산
		shape = 0;		//막대기 모양으로 리턴
	else
		shape = (rand() % 6) + 1;		//나머지 1~6

	int angle = 0;
	int color = shape + 1;

	return new Block(shape, angle, color, 5, -5);
}