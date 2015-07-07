#include "PcInputReciever.h"
#include <Windowsx.h>
#include "Logger.h"


PcInputReciever::PcInputReciever()
{
	NumberOfHandlers = 0;
	PresentableKeyboardState = new KeyboardState(CurrentKeyboardMap);
	CurrentMouseMap = new ConstantMouseState();
}


PcInputReciever::~PcInputReciever()
{
	CurrentKeyboardMap.clear();
	delete PresentableKeyboardState;
}


int PcInputReciever::AddPcHandler(PcInputHandler* _handler)
{
	if (NumberOfHandlers == MAX_HANDLERS) return 0;
	HandlerList[NumberOfHandlers] = _handler;
	++NumberOfHandlers;
	return 1;
}


int PcInputReciever::ReadInput()
{
	ClearKeyboardState();
	ClearMouseState();

	for (int i = 0; i < NumberOfHandlers; ++i)
	{
		HandlerList[i]->HandleKeyboardInput(PresentableKeyboardState);
		HandlerList[i]->HandleMouseInput(PresentableMouseState);
	}

	return 1;
}


int PcInputReciever::KeyPressed(WPARAM _key)
{
	CurrentKeyboardMap[_key] = true;
	return 1;
}


int PcInputReciever::KeyReleased(WPARAM _key)
{
	CurrentKeyboardMap[_key] = false;
	return 1;
}


int PcInputReciever::MouseMoved(LPARAM _mouse)
{
	CurrentMouseMap->SetCursorPosition(GET_X_LPARAM(_mouse), GET_Y_LPARAM(_mouse));
	return 1;
}


int PcInputReciever::MouseButtonPressed(int _button)
{
	CurrentMouseMap->SetButtonPressed(_button, true);
	return 1;
}


int PcInputReciever::MouseButtonReleased(int _button)
{
	CurrentMouseMap->SetButtonPressed(_button, false);
	return 1;
}


int PcInputReciever::ClearKeyboardState()
{
	delete PresentableKeyboardState;
	PresentableKeyboardState = new KeyboardState(CurrentKeyboardMap);
	return 1;
}

int PcInputReciever::ClearMouseState()
{
	delete PresentableMouseState;
	PresentableMouseState = new MouseState(CurrentMouseMap);
	return 1;
}