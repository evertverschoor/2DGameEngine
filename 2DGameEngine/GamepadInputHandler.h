#ifndef GAMEPADINPUTHANDLER_H
#define GAMEPADINPUTHANDLER_H

#include "GamepadState.h"
#include <Windows.h>
#include <Xinput.h>

class GamepadInputHandler
{
public:
	virtual ~GamepadInputHandler() {};
	virtual int HandleGamepadInput(GamepadState*) = 0;
	virtual int GetGamepadNumber() = 0;
};

#endif