#ifndef PCINPUTHANDLER_H
#define PCINPUTHANDLER_H

#include "KeyboardState.h"
#include "MouseState.h"

class PcInputHandler
{
public:
	virtual ~PcInputHandler() {};
	virtual int HandleKeyboardInput(KeyboardState*) = 0;
	virtual int HandleMouseInput(MouseState*) = 0;
};

#endif