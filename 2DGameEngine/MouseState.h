#define MOUSE_LBUTTON 1
#define MOUSE_RBUTTON 2
#define MOUSE_MBUTTON 3

#ifndef MOUSESTATE_H
#define MOUSESTATE_H

#include "Position.h"
#include "ConstantMouseState.h"
#include <map>

/// <summary>
/// The generic mouse state format to be read as user input.
/// </summary>
class MouseState
{
public:
	MouseState(ConstantMouseState*);
	~MouseState();

	/// <summary>
	/// Get the current cursos position relative to the window. (0,0 is top left)
	/// </summary>
	Position* GetCursorPosition();
	bool IsMouseButtonPressed(int);
private:
	Position* mousePosition;
	std::map<int, bool> mouseButtonMap;
	int SetProperties(ConstantMouseState*);
};

#endif