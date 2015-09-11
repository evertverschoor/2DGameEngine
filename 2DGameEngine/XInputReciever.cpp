#include "XInputReciever.h"


XInputReciever::XInputReciever()
{
	numberOfHandlers = 0;
	numberOfGamepads = 0;
}


XInputReciever::~XInputReciever()
{
}


int XInputReciever::AddGamepadHandler(GamepadInputHandler* _handler)
{
	if (numberOfHandlers == MAX_HANDLERS) return 0;
	handlerList[numberOfHandlers] = _handler;
	++numberOfHandlers;
	return 1;
}


int XInputReciever::ReadInput()
{
	// Read Gamepad states
	for (int i = 0; i < numberOfHandlers; ++i)
	{
		switch (handlerList[i]->HandleGamepadInput(gamepads[handlerList[i]->GetGamepadNumber()]->GetState()))
		{
			case 0: gamepads[handlerList[i]->GetGamepadNumber()]->Vibrate(0, 0); break;
			case 1: gamepads[handlerList[i]->GetGamepadNumber()]->Vibrate(MAX_VIBRATION_VALUE, 0); break;
			case 2: gamepads[handlerList[i]->GetGamepadNumber()]->Vibrate(0, MAX_VIBRATION_VALUE); break;
			case 3: gamepads[handlerList[i]->GetGamepadNumber()]->Vibrate(MAX_VIBRATION_VALUE, MAX_VIBRATION_VALUE); break;
		}
	}

	return 1;
}


bool XInputReciever::HasGamepadsConnected()
{
	Logger::Instance()->Log("\nDetecting XInput Gamepad(s)");

	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		gamepads[i] = new XInputController(i);
		if (gamepads[i]->IsConnected())
		{
			++numberOfGamepads;
		}
		else
		{
			delete gamepads[i];
		}
	}

	Logger::Instance()->Log("\nDone. Number of Gamepads detected: ");
	Logger::Instance()->Log(numberOfGamepads);

	return numberOfGamepads > 0;
}