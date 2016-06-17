#include "MenuButton.h"
#include "InputHandler.h"
#include "MenuState.h"

MenuButton::MenuButton()
	:callback(nullptr), released(true)
{
}


MenuButton::~MenuButton()
{
}


void MenuButton::Draw()
{
	SDLGameObject::Draw();
}

void MenuButton::Update()
{
	SDL_Point mousePos = TheInputHandler::Instance()->GetMousePosition();
	if (mousePos.x < (x + width) && mousePos.x > x &&
		mousePos.y < (y + height) && mousePos.y > y)
	{
		if (TheInputHandler::Instance()->GetMouseButtonState(LEFT_BUTTON) && released)
		{
			currentFrame = CLICKED;
			released = false;
			callback();

			int a =0;
			a += 4;
			return;		//�� ��ȯ ���� ��ü�� �Ҹ�ǹǷ� �������´�.
		}
		else if (TheInputHandler::Instance()->GetMouseButtonState(LEFT_BUTTON) == false)
		{
			released = true;
			currentFrame = MOUSE_OVER;
		}
		return;
	}
	currentFrame = MOUSE_OUT;
}

void MenuButton::Clean()
{
	SDLGameObject::Clean();
}