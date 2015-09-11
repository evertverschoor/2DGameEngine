#include "PcInputReciever.h"


PcInputReciever::PcInputReciever()
{
	numberOfHandlers = 0;
	presentableKeyboardState = new KeyboardState(currentKeyboardMap);
	currentMouseMap = new ConstantMouseState();
}


PcInputReciever::~PcInputReciever()
{
	currentKeyboardMap.clear();
	delete presentableKeyboardState;
}


int PcInputReciever::AddPcHandler(PcInputHandler* _handler)
{
	if (numberOfHandlers == MAX_HANDLERS) return 0;
	handlerList[numberOfHandlers] = _handler;
	++numberOfHandlers;
	return 1;
}


int PcInputReciever::ReadInput()
{
	ClearKeyboardState();
	ClearMouseState();

	for (int i = 0; i < numberOfHandlers; ++i)
	{
		handlerList[i]->HandleKeyboardInput(presentableKeyboardState);
		handlerList[i]->HandleMouseInput(presentableMouseState);
	}

	return 1;
}


int PcInputReciever::KeyPressed(WPARAM _key)
{
	currentKeyboardMap[_key] = true;
	return 1;
}


int PcInputReciever::KeyReleased(WPARAM _key)
{
	currentKeyboardMap[_key] = false;
	return 1;
}


int PcInputReciever::MouseMoved(LPARAM _mouse)
{
	currentMouseMap->SetCursorPosition(GET_X_LPARAM(_mouse), GET_Y_LPARAM(_mouse));
	return 1;
}


int PcInputReciever::MouseButtonPressed(int _button)
{
	currentMouseMap->SetButtonPressed(_button, true);
	return 1;
}


int PcInputReciever::MouseButtonReleased(int _button)
{
	currentMouseMap->SetButtonPressed(_button, false);
	return 1;
}


int PcInputReciever::ClearKeyboardState()
{
	delete presentableKeyboardState;
	presentableKeyboardState = new KeyboardState(currentKeyboardMap);
	return 1;
}

int PcInputReciever::ClearMouseState()
{
	delete presentableMouseState;
	presentableMouseState = new MouseState(currentMouseMap);
	return 1;
}