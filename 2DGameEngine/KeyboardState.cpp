#include "KeyboardState.h"


KeyboardState::KeyboardState(std::map<int, bool> _map)
{
	FinalKeyboardMap = _map;
}


KeyboardState::~KeyboardState()
{
	FinalKeyboardMap.clear();
}


bool KeyboardState::IsKeyPressed(int _key)
{
	return FinalKeyboardMap[_key];
}