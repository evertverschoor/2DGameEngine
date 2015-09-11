#ifndef CONSTANTMOUSESTATE_H
#define CONSTANTMOUSESTATE_H

#include "Position.h"
#include <map>

/// <summary>
/// The constant mouse state always has the current mouse state, a copy of this is sent to input handlers.
/// </summary>
class ConstantMouseState
{
public:
	ConstantMouseState();
	~ConstantMouseState();
	Position* GetCursorPosition();
	int SetCursorPosition(int, int);
	int SetButtonPressed(int, bool);
	bool IsMouseButtonPressed(int);
private:
	Position* cursorPosition;
	std::map<int, bool> constantMouseMap;
};

#endif