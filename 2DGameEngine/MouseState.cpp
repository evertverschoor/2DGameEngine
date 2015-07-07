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
	return MousePosition;
}


bool MouseState::IsMouseButtonPressed(int _button)
{
	if (!MouseButtonMap[_button]) return false;
	else
	{
		return MouseButtonMap[_button];
	}
}


int MouseState::SetProperties(ConstantMouseState* _mouseState)
{
	MousePosition = _mouseState->GetCursorPosition();
	MouseButtonMap[MOUSE_LBUTTON] = _mouseState->IsMouseButtonPressed(MOUSE_LBUTTON);
	MouseButtonMap[MOUSE_RBUTTON] = _mouseState->IsMouseButtonPressed(MOUSE_RBUTTON);
	MouseButtonMap[MOUSE_MBUTTON] = _mouseState->IsMouseButtonPressed(MOUSE_MBUTTON);
	return 1;
}