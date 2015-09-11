#ifndef XINPUTGAMEPADSTATE_H
#define XINPUTGAMEPADSTATE_H

#include "GamepadState.h"
#include <Windows.h>
#include <Xinput.h>

/// <summary>
/// XInput realization of the gamepad state.
/// </summary>
class XInputGamepadState : public GamepadState
{
public:
	XInputGamepadState();
	~XInputGamepadState();

	bool Start();
	bool Back();
	bool LeftTrigger();
	bool RightTrigger();
	bool LeftBumper();
	bool RightBumper();
	bool LeftStick();
	bool RightStick();
	bool A();
	bool B();
	bool X();
	bool Y();
	bool DPadDirection(int);
	bool LeftStickDirection(int);
	bool RightStickDirection(int);

	/// <summary>
	/// Update the gamepad state from an xinput_state object.
	/// </summary>
	int UpdateGamepadStateFromXinput(XINPUT_STATE);
private:
	XINPUT_STATE actualState;
};

#endif