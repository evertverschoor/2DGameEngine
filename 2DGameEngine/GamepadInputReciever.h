#ifndef GAMEPADINPUTRECIEVER_H
#define GAMEPADINPUTRECIEVER_H

#include "GamepadInputHandler.h"

class GamepadInputReciever
{
public:
	virtual ~GamepadInputReciever() {}
	virtual int AddGamepadHandler(GamepadInputHandler*) = 0;
	virtual bool HasGamepadsConnected() = 0;
	virtual int ReadInput() = 0;
};

#endif