#include "GFXController.h"


GFXController::GFXController(Renderer* _renderer)
{
	GameRenderer = _renderer;
}


GFXController::~GFXController()
{
}

int GFXController::SetMotionBlur(float _angle, float _amount)
{
	GameRenderer->SetMotionBlur(_angle, _amount);
	return 1;
}