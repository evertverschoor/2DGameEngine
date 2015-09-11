#include "XInputController.h"


XInputController::XInputController(int _gamepadno)
{
	controllerNumber = _gamepadno;
	abstractState = new XInputGamepadState();
}


XInputController::~XInputController()
{
	delete abstractState;
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
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// Get the state
	XInputGetState(controllerNumber, &controllerState);

	// Update the abstract Gamepad state
	abstractState->UpdateGamepadStateFromXinput(controllerState);

	return abstractState;
}


bool XInputController::IsConnected()
{
	// Zeroise the state
	ZeroMemory(&controllerState, sizeof(XINPUT_STATE));

	// Get the state
	DWORD _result = XInputGetState(controllerNumber, &controllerState);

	if (_result == ERROR_SUCCESS)
	{
		return true;
	}
	else
	{
		return false;
	}
}