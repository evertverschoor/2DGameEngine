#define MAX_HANDLERS 8
#define MAX_GAMEPADS 4

#ifndef XINPUTRECIEVER_H
#define XINPUTRECIEVER_H

#include "GamepadInputReciever.h"
#include "GamepadInputHandler.h"
#include "XInputController.h"
#include "Logger.h"

/// <summary>
/// XInput-realization of the gamepad input reciever.
/// </summary>
class XInputReciever : public GamepadInputReciever
{
public:
	XInputReciever();
	~XInputReciever();

	int AddGamepadHandler(GamepadInputHandler*);
	bool HasGamepadsConnected();
	int ReadInput();
private:
	GamepadInputHandler* handlerList[MAX_HANDLERS];
	XInputController* gamepads[MAX_GAMEPADS];

	int numberOfHandlers;
	int numberOfGamepads;
};

#endif