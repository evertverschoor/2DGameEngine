#define MOUSE_LBUTTON 1
#define MOUSE_RBUTTON 2
#define MOUSE_MBUTTON 3

#ifndef MOUSESTATE_H
#define MOUSESTATE_H

#include "Position.h"
#include "ConstantMouseState.h"
#include <map>

class MouseState
{
public:
	MouseState(ConstantMouseState*);
	~MouseState();
	Position* GetCursorPosition();
	bool IsMouseButtonPressed(int);
private:
	Position* MousePosition;
	std::map<int, bool> MouseButtonMap;
	int SetProperties(ConstantMouseState*);
};

#endif