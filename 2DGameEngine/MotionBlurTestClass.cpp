#include "MotionBlurTestClass.h"


MotionBlurTestClass::MotionBlurTestClass(GFXController* _controller)
{
	gfx = _controller;

	lastMouseX = 0;
	lastMouseY = 0;
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
	float _deltaX = _state->GetCursorPosition()->X - lastMouseX;
	float _deltaY = _state->GetCursorPosition()->Y - lastMouseY;

	float _angle = atan2(_deltaX, _deltaY) * (180 / PI);

	gfx->SetMotionBlur(_angle + 90, fabs(_deltaX + _deltaY) / 2);

	lastMouseX = _state->GetCursorPosition()->X;
	lastMouseY = _state->GetCursorPosition()->Y;

	return 1;
}
