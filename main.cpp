#include "Game.h"
#include "TextureManager.h"
#include "LeakCheck.h"
#include <SDL.h>


#define SEC * 1000

SDL_Window* Wnd = nullptr;
SDL_Renderer* Rend = nullptr;
SDL_Rect Rect = { 400, 0, 400, 300 };

void Init();
void PreRender();
void Render();
void PostRender();
void Release();

int main(int argc, char* argv[])
{	
	//LeakCheck();

	TheGame::Instance()->Init("20111613 KoMyeongHyun Tetrix",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 500, 600, SDL_WINDOW_SHOWN);

	const int FPS = 60;
	const Uint32 DELAY_TIME = Uint32(1000.0f / FPS);
	Uint32 frameStartTime = 0, frameTime = 0;

	while (TheGame::Instance()->Running())
	{
		frameStartTime = SDL_GetTicks();
		TheGame::Instance()->HandleEvents();
		TheGame::Instance()->Update();
		TheGame::Instance()->Render();
		
		frameTime = SDL_GetTicks() - frameStartTime;
		TheGame::Instance()->SetFrameTime(frameTime);
		//frameTime* 0.001 -> sec
		/*if (frameTime < DELAY_TIME)
		{
			SDL_Delay(DELAY_TIME - frameTime);
		}*/
	}

	TheGame::Instance()->Clean();
	delete TheGame::Instance();
	return 0;
}

void Init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	Wnd = SDL_CreateWindow("SDL Program", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 600, SDL_WINDOW_SHOWN);
	Rend = SDL_CreateRenderer(Wnd, -1, SDL_RENDERER_ACCELERATED);

	//TheTextureManager::Instance()->Load("assets/animate-alpha.png", "animate", Rend);
}
