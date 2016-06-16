#pragma once
#include <SDL.h>
#include <vector>

enum mouse_buttons
{
	LEFT_BUTTON,
	MIDDLE_BUTTON,
	RIGHT_BUTTON,
	BUTTON_COUNT
};

class InputHandler
{
public:
	static InputHandler* Instance()
	{
		static InputHandler* instance = nullptr;
		if (instance == nullptr)
		{
			instance = new InputHandler();
		}
		return instance;
	}

	~InputHandler();

	void Update();
	void Clean();
	bool IsKeyDown(SDL_Scancode key);
	bool GetMouseButtonState(mouse_buttons button) { return mouseButtonStates[button]; }
	SDL_Point GetMousePosition() { return mousePosition; }

private:
	InputHandler();
	InputHandler(const InputHandler& inputHandler);

	void OnMouseButtonDown(SDL_Event const& event);
	void OnMouseButtonUp(SDL_Event const& event);

private:
	const Uint8* keyStates;
	std::vector<bool> mouseButtonStates;
	SDL_Point mousePosition;
};

typedef InputHandler TheInputHandler;