#ifndef MOTIONBLURTESTCLASS_H
#define MOTIONBLURTESTCLASS_H

#include "PcInputHandler.h"
#include "GFXController.h"

#define PI 3.14159265358979323846

class MotionBlurTestClass : public PcInputHandler
{
public:
	MotionBlurTestClass(GFXController*);
	~MotionBlurTestClass();

	int HandleKeyboardInput(KeyboardState*);
	int HandleMouseInput(MouseState*);
private:
	GFXController* Gfx;
	int LastMouseX, LastMouseY;
};

#endif