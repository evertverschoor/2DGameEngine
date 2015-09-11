#include "MouseState.h"


MouseState::MouseState(ConstantMouseState* _mouseState)
{
	SetProperties(_mouseState);
}


MouseState::~MouseState()
{
}


Position* MouseState::GetCursorPosition()
{
	return mousePosition;
}


bool MouseState::IsMouseButtonPressed(int _button)
{
	if (!mouseButtonMap[_button]) return false;
	else
	{
		return mouseButtonMap[_button];
	}
}


int MouseState::SetProperties(ConstantMouseState* _mouseState)
{
	mousePosition = _mouseState->GetCursorPosition();
	mouseButtonMap[MOUSE_LBUTTON] = _mouseState->IsMouseButtonPressed(MOUSE_LBUTTON);
	mouseButtonMap[MOUSE_RBUTTON] = _mouseState->IsMouseButtonPressed(MOUSE_RBUTTON);
	mouseButtonMap[MOUSE_MBUTTON] = _mouseState->IsMouseButtonPressed(MOUSE_MBUTTON);
	return 1;
}