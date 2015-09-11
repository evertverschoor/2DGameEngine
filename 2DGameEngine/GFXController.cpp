#include "GFXController.h"


GFXController::GFXController(Renderer* _renderer)
{
	gameRenderer = _renderer;
}


GFXController::~GFXController()
{
}

int GFXController::SetMotionBlur(float _angle, float _amount)
{
	gameRenderer->SetMotionBlur(_angle, _amount);
	return 1;
}