#include "ConstantMouseState.h"


ConstantMouseState::ConstantMouseState()
{
	cursorPosition = new Position();
}


ConstantMouseState::~ConstantMouseState()
{
	delete cursorPosition;
}


Position* ConstantMouseState::GetCursorPosition()
{
	return cursorPosition;
}


int ConstantMouseState::SetCursorPosition(int _xPos, int _yPos)
{
	cursorPosition->X = _xPos;
	cursorPosition->Y = _yPos;

	return 1;
}


int ConstantMouseState::SetButtonPressed(int _button, bool _pressed)
{
	constantMouseMap[_button] = _pressed;
	return 1;
}


bool ConstantMouseState::IsMouseButtonPressed(int _button)
{
	if (!constantMouseMap[_button]) return false;
	else
	{
		return constantMouseMap[_button];
	}
}