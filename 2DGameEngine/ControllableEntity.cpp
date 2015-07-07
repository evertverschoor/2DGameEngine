#include "ControllableEntity.h"
#include "Logger.h"
#include <Windows.h>
#include <Xinput.h>


ControllableEntity::ControllableEntity()
{
	GamepadNumber = 0;
}


ControllableEntity::~ControllableEntity()
{
}


int ControllableEntity::HandleGamepadInput(GamepadState* _state)
{
	int _vibrate = 0;

	if (_state->LeftStickDirection(GAMEPADSTATE_UP))
	{
		JumpTo(GetPosition().X, GetPosition().Y - 3);
		++_vibrate;
	}
	if (_state->LeftStickDirection(GAMEPADSTATE_DOWN))
	{
		JumpTo(GetPosition().X, GetPosition().Y + 3);
		++_vibrate;
	}
	if (_state->LeftStickDirection(GAMEPADSTATE_LEFT))
	{
		JumpTo(GetPosition().X - 3, GetPosition().Y);
		++_vibrate;
	}
	if (_state->LeftStickDirection(GAMEPADSTATE_RIGHT))
	{
		JumpTo(GetPosition().X + 3, GetPosition().Y);
		++_vibrate;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_RIGHT))
	{
		SetDirection(GetDirection() + 3);
		++_vibrate;
	}
	if (_state->RightStickDirection(GAMEPADSTATE_LEFT))
	{
		SetDirection(GetDirection() - 3);
		++_vibrate;
	}

	return _vibrate;
}


int ControllableEntity::HandleKeyboardInput(KeyboardState* _state)
{
	if (_state->IsKeyPressed(KEY_W)) JumpTo(GetPosition().X, GetPosition().Y - 3);
	if (_state->IsKeyPressed(KEY_S)) JumpTo(GetPosition().X, GetPosition().Y + 3);
	if (_state->IsKeyPressed(KEY_A)) JumpTo(GetPosition().X - 3, GetPosition().Y);
	if (_state->IsKeyPressed(KEY_D)) JumpTo(GetPosition().X + 3, GetPosition().Y);
	return 1;
}


int ControllableEntity::HandleMouseInput(MouseState* _state)
{
	if (_state->IsMouseButtonPressed(1))
	{
		SetDirection(GetDirection() + 3);
	}
	if (_state->IsMouseButtonPressed(2))
	{
		SetDirection(GetDirection() - 3);
	}
	return 1;
}


int ControllableEntity::GetGamepadNumber()
{
	return GamepadNumber;
}