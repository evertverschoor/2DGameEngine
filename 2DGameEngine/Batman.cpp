#include "Batman.h"


Batman::Batman()
{
	// Set the asset URI for this entity
	SetAsssetURI("Assets/UI/ArkhamKnight.jpg");
}


Batman::~Batman()
{
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
	if (_state->IsKeyPressed(KEY_W)) JumpTo(GetPosition().X, GetPosition().Y - 3);
	if (_state->IsKeyPressed(KEY_S)) JumpTo(GetPosition().X, GetPosition().Y + 3);
	if (_state->IsKeyPressed(KEY_A)) JumpTo(GetPosition().X - 3, GetPosition().Y);
	if (_state->IsKeyPressed(KEY_D)) JumpTo(GetPosition().X + 3, GetPosition().Y);
	if (_state->IsKeyPressed(KEY_PLUS)) SetZindex(GetPosition().Z + 3);
	if (_state->IsKeyPressed(KEY_DASH)) SetZindex(GetPosition().Z - 3);

	return 1;
}