#include "Batman.h"


Batman::Batman()
{
	// Set the asset URI and appropriate hitbox for this entity
	SetAssetURI("Assets/UI/ArkhamKnight.jpg");
	SetHitbox(960, 600);

	// Set speed and phase property
	SetSpeed(10);
	SetPhaseState(false);
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
		SetDirection(GetDirection() + 3);
	}
	if (_state->IsMouseButtonPressed(2))
	{
		SetDirection(GetDirection() - 3);
	}

	return 1;
}


int Batman::HandleKeyboardInput(KeyboardState* _state)
{
	if (_state->IsKeyPressed(KEY_W)) JumpTo(GetPosition().X, GetPosition().Y - GetSpeed());
	if (_state->IsKeyPressed(KEY_S)) JumpTo(GetPosition().X, GetPosition().Y + GetSpeed());
	if (_state->IsKeyPressed(KEY_A)) JumpTo(GetPosition().X - GetSpeed(), GetPosition().Y);
	if (_state->IsKeyPressed(KEY_D)) JumpTo(GetPosition().X + GetSpeed(), GetPosition().Y);
	if (_state->IsKeyPressed(KEY_PLUS)) SetZindex(GetPosition().Z + GetSpeed());
	if (_state->IsKeyPressed(KEY_DASH)) SetZindex(GetPosition().Z - GetSpeed());

	return 1;
}


int Batman::HandleGamepadInput(GamepadState* _state)
{
	int _xPos = 0;
	int _yPos = 0;

	if (_state->LeftStickDirection(GAMEPADSTATE_UP)) _yPos -= 8;
	if (_state->LeftStickDirection(GAMEPADSTATE_DOWN)) _yPos += 8;
	if (_state->LeftStickDirection(GAMEPADSTATE_LEFT)) _xPos -= 8;
	if (_state->LeftStickDirection(GAMEPADSTATE_RIGHT)) _xPos += 8;

	JumpTo(GetPosition().X + _xPos, GetPosition().Y + _yPos);

	return 0;
}


int Batman::GetGamepadNumber()
{
	return 0;
}