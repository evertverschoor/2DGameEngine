#include "XInputGamepadState.h"


XInputGamepadState::XInputGamepadState()
{
}


XInputGamepadState::~XInputGamepadState()
{
}


bool XInputGamepadState::Start()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_START) ? true : false;
}


bool XInputGamepadState::Back()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_BACK) ? true : false;
}


bool XInputGamepadState::LeftTrigger()
{
	return (actualState.Gamepad.bLeftTrigger) ? true : false;
}


bool XInputGamepadState::RightTrigger()
{
	return (actualState.Gamepad.bRightTrigger) ? true : false;
}


bool XInputGamepadState::LeftBumper()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER) ? true : false;
}


bool XInputGamepadState::RightBumper()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER) ? true : false;
}


bool XInputGamepadState::LeftStick()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_LEFT_THUMB) ? true : false;
}


bool XInputGamepadState::RightStick()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_RIGHT_THUMB) ? true : false;
}


bool XInputGamepadState::A()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_A) ? true : false;
}


bool XInputGamepadState::B()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_B) ? true : false;
}


bool XInputGamepadState::X()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_X) ? true : false;
}


bool XInputGamepadState::Y()
{
	return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_Y) ? true : false;
}


bool XInputGamepadState::DPadDirection(int _direction)
{
	switch (_direction)
	{
		case GAMEPADSTATE_UP: return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP) ? true : false;
		case GAMEPADSTATE_RIGHT: return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) ? true : false;
		case GAMEPADSTATE_DOWN: return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN) ? true : false;
		case GAMEPADSTATE_LEFT: return (actualState.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) ? true : false;
		default: return false;
	}
}


bool XInputGamepadState::LeftStickDirection(int _direction)
{
	switch (_direction)
	{
		case GAMEPADSTATE_UP: return (actualState.Gamepad.sThumbLY > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		case GAMEPADSTATE_DOWN: return (actualState.Gamepad.sThumbLY < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		case GAMEPADSTATE_RIGHT: return (actualState.Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		case GAMEPADSTATE_LEFT: return (actualState.Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) ? true : false;
		default: return false;
	}
}


bool XInputGamepadState::RightStickDirection(int _direction)
{
	switch (_direction)
	{
	case GAMEPADSTATE_UP: return (actualState.Gamepad.sThumbRY > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	case GAMEPADSTATE_DOWN: return (actualState.Gamepad.sThumbRY < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	case GAMEPADSTATE_RIGHT: return (actualState.Gamepad.sThumbRX > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	case GAMEPADSTATE_LEFT: return (actualState.Gamepad.sThumbRX < -XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) ? true : false;
	default: return false;
	}
}


int XInputGamepadState::UpdateGamepadStateFromXinput(XINPUT_STATE _state)
{
	actualState = _state;
	return 1;
}