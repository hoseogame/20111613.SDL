#include "PlayGround.h"
#include "Game.h"
#include "BlockManager.h"
#include "GroundBlockManager.h"
#include "InputHandler.h"
#include "GameStateMachine.h"
#include "MenuState.h"
//#include <SDL_ttf.h>


PlayGround::PlayGround()
{
	firstPress[UP] = false;
	firstPress[LEFT] = false;
	firstPress[RIGHT] = false;

	/*TTF_Font* sans = TTF_OpenFont("Times.ttf", 24);
	SDL_Color black = { 255, 0, 255 };
	surfaceMessage = TTF_RenderText_Solid(sans, "Levelvv", black);*/
}


PlayGround::~PlayGround()
{
	delete blockManager;
	blockManager = nullptr;

	delete groundBlockManager;
	groundBlockManager = nullptr;
}

void PlayGround::Init()
{
	//Load후에 호출 되어야 한다.
	blockManager = new BlockManager(textureID);
	groundBlockManager = new GroundBlockManager(textureID);

	groundBlockManager->Init();
	blockManager->Init();
}

void PlayGround::Draw()
{
	groundBlockManager->Draw();
	blockManager->Draw();

	/*SDL_Texture* Message = SDL_CreateTextureFromSurface(TheGame::Instance()->GetRenderer(), surfaceMessage);
	SDL_Rect Message_rect;
	Message_rect.x = 100;
	Message_rect.y = 100;
	Message_rect.w = 10;
	Message_rect.h = 10;
	SDL_RenderCopy(TheGame::Instance()->GetRenderer(), Message, NULL, &Message_rect);*/
	
}

void PlayGround::Update()
{
	blockManager->MakeNewBlock();
	groundBlockManager->EraseFullLine(blockManager->OngoingBlock());

	if (groundBlockManager->ProcessFullLine() == true)
	{
		return;
	}

	static Uint32 inputActionTime = 0;
	static Uint32 limitTIme = 60;
	inputActionTime += TheGame::Instance()->GetFrameTime();
	if (inputActionTime > limitTIme)
	{
		//눌린 후 한번만 이동하고 일정시간 이상 눌리면 계속 이동
		if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) && firstPress[UP] == true)
		{
			groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), ROTATE);
		}
		else if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_DOWN))
		{
			groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), DOWN_MOVE);
		}

		if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) && firstPress[LEFT] == true)
		{
			groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), LEFT_MOVE);
		}
		else if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) && firstPress[RIGHT] == true)
		{
			groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), RIGHT_MOVE);
		}

		inputActionTime = 0;
		limitTIme = 60;
	}

	if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) && firstPress[UP] == false)
	{
		firstPress[UP] = true;
		inputActionTime = 0;
		limitTIme = 300;

		groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), ROTATE);
	}
	else if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_UP) == false)
	{
		firstPress[UP] = false;
	}

	if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) && firstPress[LEFT] == false)
	{
		firstPress[LEFT] = true;
		inputActionTime = 0;
		limitTIme = 300;

		groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), LEFT_MOVE);
	}
	else if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) && firstPress[RIGHT] == false)
	{
		firstPress[RIGHT] = true;
		inputActionTime = 0;
		limitTIme = 300;

		groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), RIGHT_MOVE);
	}

	if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_LEFT) == false)
	{
		firstPress[LEFT] = false;
	}
	if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_RIGHT) == false)
	{
		firstPress[RIGHT] = false;
	}



	static Uint32 actionTime = 0;
	bool stop = false;
	if (TheInputHandler::Instance()->IsKeyDown(SDL_SCANCODE_SPACE))
	{
		while (stop == false)
		{
			stop = !groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), DOWN_MOVE);
		}

		actionTime = 600;
		return;
	}

	//일정 시간마다 움직이도록, 게임 난이도 조절
	actionTime += TheGame::Instance()->GetFrameTime();
	if (actionTime < 600)
	{
		return;
	}
	else
	{
		actionTime -= 600;
	}

	stop = !groundBlockManager->TranslateBlock(blockManager->OngoingBlock(), DOWN_MOVE);
	if (stop == true)
	{
		//블럭이 한계치에 닿을 경우 게임오버
		if (blockManager->OngoingBlock()->GetY() < 1)
		{
			TheGame::Instance()->GetGameStateMachine()->ChangeState(new MenuState());
			return;
		}

		groundBlockManager->CheckFullLine();
		blockManager->SetBeOngoingBlock(false);
	}
}

void PlayGround::Clean()
{}

void PlayGround::Load(const LoaderParams* params)
{
	SDLGameObject::Load(params);
	Init();
}