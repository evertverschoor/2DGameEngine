#include "XInputReciever.h"
#include "Logger.h"
#include <Windows.h>
#include <Xinput.h>


XInputReciever::XInputReciever()
{
	NumberOfHandlers = 0;
	NumberOfGamepads = 0;
}


XInputReciever::~XInputReciever()
{
}


int XInputReciever::AddGamepadHandler(GamepadInputHandler* _handler)
{
	if (NumberOfHandlers == MAX_HANDLERS) return 0;
	HandlerList[NumberOfHandlers] = _handler;
	++NumberOfHandlers;
	return 1;
}


int XInputReciever::ReadInput()
{
	// Read Gamepad states
	for (int i = 0; i < NumberOfHandlers; ++i)
	{
		switch (HandlerList[i]->HandleGamepadInput(Gamepads[HandlerList[i]->GetGamepadNumber()]->GetState()))
		{
			case 0: Gamepads[HandlerList[i]->GetGamepadNumber()]->Vibrate(0, 0); break;
			case 1: Gamepads[HandlerList[i]->GetGamepadNumber()]->Vibrate(MAX_VIBRATION_VALUE, 0); break;
			case 2: Gamepads[HandlerList[i]->GetGamepadNumber()]->Vibrate(0, MAX_VIBRATION_VALUE); break;
			case 3: Gamepads[HandlerList[i]->GetGamepadNumber()]->Vibrate(MAX_VIBRATION_VALUE, MAX_VIBRATION_VALUE); break;
		}
	}

	return 1;
}


bool XInputReciever::HasGamepadsConnected()
{
	Logger::Instance()->Log("\nDetecting XInput Gamepad(s)");

	for (int i = 0; i < MAX_GAMEPADS; ++i)
	{
		Gamepads[i] = new X360Controller(i);
		if (Gamepads[i]->IsConnected())
		{
			++NumberOfGamepads;
		}
		else
		{
			delete Gamepads[i];
		}
	}

	Logger::Instance()->Log("\nDone. Number of Gamepads detected: ");
	Logger::Instance()->Log(NumberOfGamepads);

	return NumberOfGamepads > 0;
}