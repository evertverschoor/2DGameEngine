#include "XInputController.h"
#include <Windows.h>


XInputController::XInputController(int _gamepadno)
{
	ControllerNumber = _gamepadno;
	AbstractState = new XInputGamepadState();
}


XInputController::~XInputController()
{
	delete AbstractState;
}


int XInputController::Vibrate(int _left, int _right)
{
	// Ensure the values are within the controller's constraints
	if (_left > MAX_VIBRATION_VALUE) _left = MAX_VIBRATION_VALUE;
	else if (_left < 0) _left = 0;
	else if (_right > MAX_VIBRATION_VALUE) _right = MAX_VIBRATION_VALUE;
	else if (_right < 0) _right = 0;

	// Create a Vibraton State
	XINPUT_VIBRATION Vibration;

	// Zeroise the Vibration
	ZeroMemory(&Vibration, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	Vibration.wLeftMotorSpeed = _left;
	Vibration.wRightMotorSpeed = _right;

	// Vibrate the controller
	XInputSetState(0, &Vibration);

	return 1;
}


XInputGamepadState* XInputController::GetState()
{
	// Zeroise the state
	ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(ControllerNumber, &ControllerState);

	// Update the abstract Gamepad state
	AbstractState->UpdateGamepadStateFromXinput(ControllerState);

	return AbstractState;
}


bool XInputController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&ControllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD Result = XInputGetState(ControllerNumber, &ControllerState);

	if (Result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}