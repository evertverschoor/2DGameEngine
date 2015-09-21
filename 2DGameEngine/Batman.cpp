#include "Batman.h"


Batman::Batman()
{
	// Add asset Uri and set it as currently showing
	AddAsset("main", "Assets/UI/ArkhamKnight.jpg");
	AddAsset("neko", "Assets/Characters/Shigure.png");

	SetCurrentAsset("neko");

	// Set hit box as same size as image
	SetHitbox(184, 184);

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
	bool _up = _state->IsKeyPressed(KEY_W);
	bool _left = _state->IsKeyPressed(KEY_A);
	bool _down = _state->IsKeyPressed(KEY_S);
	bool _right = _state->IsKeyPressed(KEY_D);

	// Move based on them
	MoveFromInput(_up, _left, _down, _right);

	return 1;
}


int Batman::HandleGamepadInput(GamepadState* _state)
{
	// Grab important gamepad input
	bool _up = _state->LeftStickDirection(GAMEPADSTATE_UP);
	bool _left = _state->LeftStickDirection(GAMEPADSTATE_LEFT);
	bool _down = _state->LeftStickDirection(GAMEPADSTATE_DOWN);
	bool _right = _state->LeftStickDirection(GAMEPADSTATE_RIGHT);

	// Move based on them
	MoveFromInput(_up, _left, _down, _right);

	return 0;
}


int Batman::MoveFromInput(bool _up, bool _left, bool _down, bool _right)
{
	float _xMove = 0.0f;
	float _yMove = 0.0f;

	if (_up)
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