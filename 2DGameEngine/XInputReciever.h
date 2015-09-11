#define MAX_HANDLERS 8
#define MAX_GAMEPADS 4

#ifndef XINPUTRECIEVER_H
#define XINPUTRECIEVER_H

#include "GamepadInputReciever.h"
#include "GamepadInputHandler.h"
#include "XInputController.h"
#include <Windows.h>
#include <Xinput.h>

class XInputReciever : public GamepadInputReciever
{
public:
	XInputReciever();
	~XInputReciever();

	int AddGamepadHandler(GamepadInputHandler*);
	bool HasGamepadsConnected();
	int ReadInput();
private:
	GamepadInputHandler* HandlerList[MAX_HANDLERS];
	XInputController* Gamepads[MAX_GAMEPADS];

	int NumberOfHandlers;
	int NumberOfGamepads;
};

#endif