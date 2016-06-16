#include "GroundBlockManager.h"
#include "TextureManager.h"
#include "Game.h"

const char GroundBlockManager::blockShape[SHAPE_COUNT][ANGLE_COUNT][FIELD_WIDTH][FIELD_HEIGHT] =
{
	//막대모양
	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,0,0,0,1,0,0,0,	1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,

	//네모모양
	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,1,0,0,1,1,0,0,0,0,0,0,0,0,0,0,

	//'ㅓ' 모양
	0,1,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	0,1,0,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'ㄱ'모양
	1,1,0,0,0,1,0,0,0,1,0,0,0,0,0,0,	1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,0,0,0,1,1,0,0,0,0,0,0,	0,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,

	//'ㄴ' 모양
	1,1,0,0,1,0,0,0,1,0,0,0,0,0,0,0,	1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,0,1,0,0,1,1,0,0,0,0,0,0,	1,1,1,0,0,0,1,0,0,0,0,0,0,0,0,0,

	//'Z' 모양
	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,	1,1,0,0,0,1,1,0,0,0,0,0,0,0,0,0,	0,1,0,0,1,1,0,0,1,0,0,0,0,0,0,0,

	//'S' 모양
	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0,	0,1,1,0,1,1,0,0,0,0,0,0,0,0,0,0,	1,0,0,0,1,1,0,0,0,1,0,0,0,0,0,0
};

GroundBlockManager::GroundBlockManager(std::string _textureID) : textureID(_textureID)
{
	groundBlock = new GroundBlock*[ground_size::HEIGHT];
	completeDestruction = new bool[ground_size::HEIGHT];
	for (int i = 0; i < ground_size::HEIGHT; ++i)
	{
		groundBlock[i] = new GroundBlock[ground_size::WIDTH];
		completeDestruction[i] = false;
	}

	srcRect.x = 0;
	srcRect.y = 0;
	srcRect.w = IMG_SIZE;
	srcRect.h = IMG_SIZE;

	destRect.x = 0;
	destRect.y = 0;
	destRect.w = BLOCK_SIZE;
	destRect.h = BLOCK_SIZE;
}


GroundBlockManager::~GroundBlockManager()
{
	for (int i = 0; i < ground_size::HEIGHT; ++i)
	{
		delete[] groundBlock[i];
	}
	delete[] groundBlock;
	delete[] completeDestruction;
	destructionBlocks.clear();
}

void GroundBlockManager::Init()
{
	int const h = ground_size::HEIGHT - 1;
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < ground_size::WIDTH; ++j)
		{
			if ((j == START_W) || (j == END_W))
			{
				groundBlock[i][j].existence = 1;
			}
			else
			{
				groundBlock[i][j].existence = 0;
			}
			groundBlock[i][j].color = block_color::WHITE;
			groundBlock[i][j].destruction = false;
			groundBlock[i][j].frame = 0;
		}
	}

	//ground의 가장 밑의 줄은 1로 채운다.
	for (int j = 0; j < ground_size::WIDTH; ++j)
	{
		groundBlock[ground_size::END_H][j].existence = 1;
		groundBlock[ground_size::END_H][j].color = block_color::WHITE;
		groundBlock[ground_size::END_H][j].destruction = false;
		groundBlock[ground_size::END_H][j].frame = 0;
	}
}

void GroundBlockManager::Draw()
{
	SDL_Point d_pos;
	static Uint32 changeTime = 0;

	for (int i = 0; i < ground_size::HEIGHT; ++i)
	{
		for (int j = 0; j < ground_size::WIDTH; ++j)
		{
			if (groundBlock[i][j].existence == 0)
			{
				continue;
			}

			if (groundBlock[i][j].destruction == true)
			{
				d_pos = destructionBlocks.front();
				
				if (d_pos.x == j && d_pos.y == i)
				{
					//시간에 따른 프레임 변화
					changeTime += TheGame::Instance()->GetFrameTime();
					if (changeTime > 10)
					{
						changeTime = 0;
						++(groundBlock[i][j].frame);
					}

					//마지막 프레임일 때
					if (groundBlock[i][j].frame > DESTRUCTION_FRAME_COUNT) 
					{
						if ( j == (END_W-1) )
						{
							completeDestruction[i] = true;
						}
						destructionBlocks.pop_front();
					}
				}

				//source의 x 값이 frame에 따라 변한다.
				srcRect.x = IMG_SIZE*groundBlock[i][j].frame; 
				srcRect.y = IMG_SIZE;
			}
			else
			{
				//source의 x 값이 색상에 따라 변한다.
				srcRect.x = groundBlock[i][j].color * IMG_SIZE;
				srcRect.y = 0;
			}
			destRect.x = START_GROUND_X + ground_size::BLOCK_SIZE * j;
			destRect.y = START_GROUND_Y + ground_size::BLOCK_SIZE * i;


			TheTextureManager::Instance()->DrawStoD(textureID, srcRect, destRect, TheGame::Instance()->GetRenderer());
		}
	}
}

bool GroundBlockManager::TranslateBlock(Block* const block, block_behavior const behavior)
{
	//기존 부분 지우고
	EraseBlockOfScreen(block);

	//멤버함수포인터를 통해 행동에 맞는 동작을 할 수 있도록
	static TranslateEvent fp[BEHAVIOR_COUNT] = { &GroundBlockManager::DownMoveBlock,
		&GroundBlockManager::LeftMoveBlock, &GroundBlockManager::RightMoveBlock, &GroundBlockManager::RotateBlock };

	bool translation = (this->*fp[behavior])(block);
	
	//새롭게 그려준다.
	ShowBlockOfScreen(block);

	return translation;
}

bool GroundBlockManager::DownMoveBlock(Block* const block)
{
	if (StrikeCheck(block, 0, MOVE_COUNT) == false)
	{
		block->Move();
		return true;
	}
	return false;
}

bool GroundBlockManager::LeftMoveBlock(Block* const block)
{
	if (StrikeCheck(block, -MOVE_COUNT, 0) == false)
	{
		block->SetX(block->GetX() - MOVE_COUNT);
		return true;
	}
	return false;
}

bool GroundBlockManager::RightMoveBlock(Block* const block)
{
	if (StrikeCheck(block, MOVE_COUNT, 0) == false)
	{
		block->SetX(block->GetX() + MOVE_COUNT);
		return true;
	}
	return false;
}

bool GroundBlockManager::RotateBlock(Block* const block)
{
	if (StrikeCheck(block, 0, 0, ROTATION_COUNT) == false)
	{
		block->SetAngle( (block->GetAngle() + ROTATION_COUNT) % ANGLE_COUNT );
		return true;
	}
	return false;
}

void GroundBlockManager::CheckFullLine()
{
	int i = 0, j = 0;
	for (i = 0; i < ground_size::END_H; ++i)
	{
		for (j = 1; j < ground_size::END_W; ++j)
		{
			if (groundBlock[i][j].existence == 0)
			{
				break;
			}
		}

		if (j != ground_size::END_W)
		{
			continue;
		}

		//애니메이션이 재생되도록 설정
		for (j = 1; j < ground_size::END_W; ++j)
		{
			groundBlock[i][j].destruction = true;

			SDL_Point d_pos;
			d_pos.x = j, d_pos.y = i;
			destructionBlocks.push_back(d_pos);
		}
	}
}

void GroundBlockManager::EraseFullLine(Block* const block)
{
	int i = 0, j = 0;
	for (i = 0; i < ground_size::END_H; ++i)
	{
		if (groundBlock[i][1].destruction == false || completeDestruction[i] == false)
		{
			continue;
		}

		for (int k = i; k > START_H; --k)
		{
			for (j = 1; j < ground_size::END_W; ++j)
			{
				groundBlock[k][j] = groundBlock[k - 1][j];
			}
		}
		for (j = 1; j < ground_size::END_W; ++j)
		{
			groundBlock[START_H][j].existence = 0;
			groundBlock[START_H][j].destruction = false;
			groundBlock[START_H][j].frame = 0;
		}

		completeDestruction[i] = false;
	}
}

bool GroundBlockManager::ProcessFullLine()
{
	for (int i = 0; i < ground_size::END_H; ++i)
	{
		if (groundBlock[i][1].destruction == true)
		{
			return true;
		}
	}

	return false;
}

bool GroundBlockManager::StrikeCheck(Block* const block, int add_x, int add_y, int add_angle)
{
	int x_ = block->GetX() + add_x;
	int y_ = block->GetY() + add_y;
	int angle_ = (block->GetAngle() + add_angle) % ANGLE_COUNT;
	char exist = 0;

	if(x_ < 1)
	{
		return true;
	}

	for (int i = 0; i < block_shape::FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < block_shape::FIELD_WIDTH; ++j)
		{

			if((y_ + i) < 0)
			{
				if ((x_ + j) <= 0 || (x_ + j) >= (ground_size::WIDTH - 1))
				{
					exist = blockShape[block->GetShape()][angle_][i][j];
					if (exist == 1)
					{
						return true;
					}
				}
			}

			if ( (x_ + j) < 0 || (x_ + j) >= ground_size::WIDTH
				|| (y_ + i) < 0 || (y_ + i) >= ground_size::HEIGHT )	//맵을 벗어나면 연산에서 제외
			{
				continue;
			}

			exist = blockShape[block->GetShape()][angle_][i][j];
			if (exist == 0)
			{
				continue;
			}
			else if (exist == groundBlock[y_ + i][x_ + j].existence)
			{
				return true;
			}
		}
	}

	return false;
}

void GroundBlockManager::EraseBlockOfScreen(Block* const block)
{
	int x_ = block->GetX();
	int y_ = block->GetY();

	for (int i = 0; i < block_shape::FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < block_shape::FIELD_WIDTH; ++j)
		{
			if ((x_ + j) < 0 || (x_ + j) >= ground_size::WIDTH
				|| (y_ + i) < 0 || (y_ + i) >= ground_size::HEIGHT)	//맵을 벗어나면 연산에서 제외
			{
				continue;
			}

			if (blockShape[block->GetShape()][block->GetAngle()][i][j] == 1)
			{
				groundBlock[y_ + i][x_ + j].existence = 0;
				groundBlock[y_ + i][x_ + j].color = block_color::WHITE;
			}
		}
	}
}

void GroundBlockManager::ShowBlockOfScreen(Block* const block)
{
	int x_ = block->GetX();
	int y_ = block->GetY();

	for (int i = 0; i < block_shape::FIELD_HEIGHT; ++i)
	{
		for (int j = 0; j < block_shape::FIELD_WIDTH; ++j)
		{
			if ((x_ + j) < 0 || (x_ + j) >= ground_size::WIDTH
				|| (y_ + i) < 0 || (y_ + i) >= ground_size::HEIGHT)	//맵을 벗어나면 연산에서 제외
			{
				continue;
			}

			//블럭 인스턴스를 GroundBlock에 반영
			if (blockShape[block->GetShape()][block->GetAngle()][i][j] == 1)
			{
				groundBlock[y_ + i][x_ + j].existence = 1;
				groundBlock[y_ + i][x_ + j].color = block->GetColor();
			}
		}
	}
}
