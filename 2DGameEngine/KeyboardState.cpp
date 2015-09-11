#include "KeyboardState.h"


KeyboardState::KeyboardState(std::map<int, bool> _map)
{
	finalKeyboardMap = _map;
}


KeyboardState::~KeyboardState()
{
	finalKeyboardMap.clear();
}


bool KeyboardState::IsKeyPressed(int _key)
{
	return finalKeyboardMap[_key];
}