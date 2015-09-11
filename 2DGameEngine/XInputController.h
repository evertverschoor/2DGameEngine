#define MAX_VIBRATION_VALUE 65535
#ifndef XINPUTCONTROLLER_H
#define XINPUTCONTROLLER_H

#include "XInputGamepadState.h"
#include <Xinput.h>

/// <summary>
/// An XInput-based controller (Xbox 360/Xbox one controllers, or any input reciever from third-party apps like DS4Windows)
/// </summary>
class XInputController
{
public:
	/// <summary>
	/// @param The gamepad number.
	/// </summary>
	XInputController(int);
	~XInputController();

	/// <summary>
	/// Returns the controller state with any buttons pressed.
	/// </summary>
	XInputGamepadState* GetState();

	/// <summary>
	/// Returns whether or not there is a controller connected on this controller number.
	/// </summary>
	bool IsConnected();

	/// <summary>
	/// Vibrate the controller.
	/// @param1 The left vibration intensity
	/// @param2 The right vibration intensity
	/// </summary>
	int Vibrate(int, int);
private:
	int controllerNumber;
	XINPUT_STATE controllerState;
	XInputGamepadState* abstractState;
};

#endif