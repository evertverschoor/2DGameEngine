#include "Batman.h"


Batman::Batman()
{
	// Add asset Uri and set it as currently showing
	AddAsset("right", "Assets/Characters/pidor_right.png");
	AddAsset("left", "Assets/Characters/pidor_left.png");

	SetCurrentAsset("right");

	// Set hit box as same size as image
	SetHitbox(222, 172);

	// Set speed and phase property
	SetSpeed(10);
	SetPhaseState(false);
	SetFloatState(false);
}


Batman::~Batman()
{
}


int Batman::Act()
{
	return 1;
}


int Batman::HandleMouseInput(MouseState* _state)
{
	if (_state->IsMouseButtonPressed(1))
	{
		Rotate(GetSpeed());
	}
	if (_state->IsMouseButtonPressed(2))
	{
		Rotate(-GetSpeed());
	}

	return 1;
}


int Batman::HandleKeyboardInput(KeyboardState* _state)
{
	// Grab important keyboard input
	bool _jump = _state->IsKeyPressed(KEY_SPACE);
	bool _left = _state->IsKeyPressed(KEY_A);
	bool _right = _state->IsKeyPressed(KEY_D);

	// Move based on them
	MoveFromInput(_jump, _left, false, _right);

	// Set the correct asset
	if (_right && !_left) SetCurrentAsset("right");
	else if (!_right && _left) SetCurrentAsset("left");

	return 1;
}


int Batman::HandleGamepadInput(GamepadState* _state)
{
	// Grab important gamepad input
	bool _jump = _state->A();
	bool _left = _state->LeftStickDirection(GAMEPADSTATE_LEFT);
	bool _right = _state->LeftStickDirection(GAMEPADSTATE_RIGHT);

	// Move based on them
	MoveFromInput(_jump, _left, false, _right);

	// Set the correct asset
	if (_right && !_left) SetCurrentAsset("right");
	else if (!_right && _left) SetCurrentAsset("left");

	return 0;
}


int Batman::MoveFromInput(bool _jump, bool _left, bool _down, bool _right)
{
	float _xMove = 0.0f;
	float _yMove = 0.0f;

	if (_jump)
	{
		_yMove -= 1.0f;
		_xMove /= 2;
	}
	if (_left)
	{
		_xMove -= 1.0f;
		_yMove /= 2;
	}
	if (_down)
	{
		_yMove += 1.0f;
		_xMove /= 2;
	}
	if (_right)
	{
		_xMove += 1.0f;
		_yMove /= 2;
	}

	Move(_xMove, _yMove);

	return 1;
}


int Batman::GetGamepadNumber()
{
	return 0;
}


int Batman::HandleCollision(Entity* _entity)
{
	return 1;
}


int Batman::Tell(int)
{
	return 1;
}