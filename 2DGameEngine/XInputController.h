#define MAX_VIBRATION_VALUE 65535
#ifndef XINPUTCONTROLLER_H
#define XINPUTCONTROLLER_H

#include "XInputGamepadState.h"
#include <Windows.h>
#include <Xinput.h>

class XInputController
{
public:
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
	int ControllerNumber;
	XINPUT_STATE ControllerState;
	XInputGamepadState* AbstractState;
};

#endif