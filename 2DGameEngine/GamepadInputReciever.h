#ifndef GAMEPADINPUTRECIEVER_H
#define GAMEPADINPUTRECIEVER_H

#include "GamepadInputHandler.h"

/// <summary>
/// The gamepad input reciever will listen to the gamepad and send its input in a proper format to all gamepad input handlers.
/// </summary>
class GamepadInputReciever
{
public:
	virtual ~GamepadInputReciever() {}

	/// <summary>
	/// Add a gamepad handler that will recieve gamepad input.
	/// </summary>
	virtual int AddGamepadHandler(GamepadInputHandler*) = 0;

	/// <summary>
	/// Returns if there are any gamepads currently connected.
	/// </summary>
	virtual bool HasGamepadsConnected() = 0;

	/// <summary>
	/// Read the gamepad input right now.
	/// </summary>
	virtual int ReadInput() = 0;
};

#endif