#include "XInputGamepadState.h"


XInputGamepadState::XInputGamepadState()
{
}


XInputGamepadState::~XInputGamepadState()
{
}


bool XInputGamepadState::Start()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? true : false;
}


bool XInputGamepadState::Back()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? true : false;
}


bool XInputGamepadState::LeftTrigger()
{
	return (ActualState.Gamepad.bLeftTrigger) ? true : false;
}


bool XInputGamepadState::RightTrigger()
{
	return (ActualState.Gamepad.bRightTrigger) ? true : false;
}


bool XInputGamepadState::LeftBumper()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? true : false;
}


bool XInputGamepadState::RightBumper()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? true : false;
}


bool XInputGamepadState::LeftStick()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? true : false;
}


bool XInputGamepadState::RightStick()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? true : false;
}


bool XInputGamepadState::A()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? true : false;
}


bool XInputGamepadState::B()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? true : false;
}


bool XInputGamepadState::X()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? true : false;
}


bool XInputGamepadState::Y()
{
	return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? true : false;
}


bool XInputGamepadState::DPadDirection(int _direction)
{
	switch (_direction)
	{
		case GAMEPADSTATE_UP: return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? true : false;
		case GAMEPADSTATE_RIGHT: return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? true : false;
		case GAMEPADSTATE_DOWN: return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? true : false;
		case GAMEPADSTATE_LEFT: return (ActualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? true : false;
		default: return false;
	}
}


bool XInputGamepadState::LeftStickDirection(int _direction)
{
	switch (_direction)
	{
		case GAMEPADSTATE_UP: return (ActualState.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		case GAMEPADSTATE_DOWN: return (ActualState.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		case GAMEPADSTATE_RIGHT: return (ActualState.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		case GAMEPADSTATE_LEFT: return (ActualState.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		default: return false;
	}
}


bool XInputGamepadState::RightStickDirection(int _direction)
{
	switch (_direction)
	{
	case GAMEPADSTATE_UP: return (ActualState.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	case GAMEPADSTATE_DOWN: return (ActualState.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	case GAMEPADSTATE_RIGHT: return (ActualState.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	case GAMEPADSTATE_LEFT: return (ActualState.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	default: return false;
	}
}


int XInputGamepadState::UpdateGamepadStateFromXinput(XINPUT_STATE _state)
{
	ActualState = _state;
	return 1;
}