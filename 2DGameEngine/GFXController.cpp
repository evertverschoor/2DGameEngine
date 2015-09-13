#include "GFXController.h"


GFXController::GFXController()
{
	motionBlurAmount = 0.0f;
	motionBlurAngle = 0.0f;
}


GFXController::~GFXController()
{
}

int GFXController::SetMotionBlur(float _angle, float _amount)
{
	motionBlurAngle = _angle;
	motionBlurAmount = _amount;

	return 1;
}


float GFXController::GetMotionBlurAmount()
{
	return motionBlurAmount;
}


float GFXController::GetMotionBlurAngle()
{
	return motionBlurAngle;
}