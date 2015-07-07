#include "ConstantMouseState.h"


ConstantMouseState::ConstantMouseState()
{
	CursorPosition = new Position();
}


ConstantMouseState::~ConstantMouseState()
{
	delete CursorPosition;
}


Position* ConstantMouseState::GetCursorPosition()
{
	return CursorPosition;
}


int ConstantMouseState::SetCursorPosition(int _xPos, int _yPos)
{
	CursorPosition->X = _xPos;
	CursorPosition->Y = _yPos;
	return 1;
}


int ConstantMouseState::SetButtonPressed(int _button, bool _pressed)
{
	ConstantMouseMap[_button] = _pressed;
	return 1;
}


bool ConstantMouseState::IsMouseButtonPressed(int _button)
{
	if (!ConstantMouseMap[_button]) return false;
	else
	{
		return ConstantMouseMap[_button];
	}
}