#ifndef CONSTANTMOUSESTATE_H
#define CONSTANTMOUSESTATE_H

#include "Position.h"
#include <map>

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
	Position* CursorPosition;
	std::map<int, bool> ConstantMouseMap;
};

#endif