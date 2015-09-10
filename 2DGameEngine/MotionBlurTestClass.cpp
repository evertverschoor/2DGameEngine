#include "MotionBlurTestClass.h"
#include "Logger.h"


MotionBlurTestClass::MotionBlurTestClass(GFXController* _controller)
{
	Gfx = _controller;

	LastMouseX = 0;
	LastMouseY = 0;
}


MotionBlurTestClass::~MotionBlurTestClass()
{
}

int MotionBlurTestClass::HandleKeyboardInput(KeyboardState* _state)
{
	return 1;
}

int MotionBlurTestClass::HandleMouseInput(MouseState* _state)
{
	float _deltaX = _state->GetCursorPosition()->X - LastMouseX;
	float _deltaY = _state->GetCursorPosition()->Y - LastMouseY;

	float _angle = atan2(_deltaX, _deltaY) * (180 / PI);

	Gfx->SetMotionBlur(_angle + 90, fabs(_deltaX + _deltaY) / 2);

	LastMouseX = _state->GetCursorPosition()->X;
	LastMouseY = _state->GetCursorPosition()->Y;

	return 1;
}
