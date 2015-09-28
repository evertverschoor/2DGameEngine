#include "GFXController.h"


GFXController::GFXController()
{
	motionBlurToggle = true;
}


GFXController::~GFXController()
{
}

int GFXController::SetMotionBlur(bool _value)
{
	motionBlurToggle = _value;
	return 1;
}


bool GFXController::MotionBlurOn()
{
	return motionBlurToggle;
}