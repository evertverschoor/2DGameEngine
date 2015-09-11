#define PI 3.14159265358979323846

#ifndef MOTIONBLURTESTCLASS_H
#define MOTIONBLURTESTCLASS_H

#include "PcInputHandler.h"
#include "GFXController.h"

/// <summary>
/// The motion blur test class will apply motion blur every time the mouse moves.
/// </summary>
class MotionBlurTestClass : public PcInputHandler
{
public:
	MotionBlurTestClass(GFXController*);
	~MotionBlurTestClass();

	int HandleKeyboardInput(KeyboardState*);
	int HandleMouseInput(MouseState*);
private:
	GFXController* gfx;
	int lastMouseX, lastMouseY;
};

#endif