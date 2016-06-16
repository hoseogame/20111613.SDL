#include "InputHandler.h"
#include "Game.h"


InputHandler::InputHandler() : keyStates(SDL_GetKeyboardState(NULL))
{
	for (int i = 0; i < mouse_buttons::BUTTON_COUNT; ++i)
	{
		mouseButtonStates.push_back(false);
	}
	mousePosition.x = 0;
	mousePosition.y = 0;
}


InputHandler::~InputHandler()
{
}


void InputHandler::Update()
{
	SDL_Event event;
	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			TheGame::Instance()->Quit();
			break;
		case SDL_KEYUP:
			keyStates = SDL_GetKeyboardState(NULL);
			break;
		case SDL_KEYDOWN:
			keyStates = SDL_GetKeyboardState(NULL);
			break;
		case SDL_MOUSEMOTION:
			mousePosition.x = event.motion.x;
			mousePosition.y = event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			OnMouseButtonDown(event);
			break;
		case SDL_MOUSEBUTTONUP:
			OnMouseButtonUp(event);
			break;
		default:
			break;
		}
	}
}

void InputHandler::Clean()
{

}

bool InputHandler::IsKeyDown(SDL_Scancode key)
{
	if (keyStates == 0)
	{
		return false;
	}

	if(keyStates[key] == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void InputHandler::OnMouseButtonDown(SDL_Event const& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[mouse_buttons::LEFT_BUTTON] = true;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[mouse_buttons::MIDDLE_BUTTON] = true;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[mouse_buttons::RIGHT_BUTTON] = true;
	}
}

void InputHandler::OnMouseButtonUp(SDL_Event const& event)
{
	if (event.button.button == SDL_BUTTON_LEFT)
	{
		mouseButtonStates[mouse_buttons::LEFT_BUTTON] = false;
	}
	if (event.button.button == SDL_BUTTON_MIDDLE)
	{
		mouseButtonStates[mouse_buttons::MIDDLE_BUTTON] = false;
	}
	if (event.button.button == SDL_BUTTON_RIGHT)
	{
		mouseButtonStates[mouse_buttons::RIGHT_BUTTON] = false;
	}
}