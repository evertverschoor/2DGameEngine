#include "TimeController.h"


TimeController* TimeController::t_instance = NULL;


TimeController::~TimeController()
{
}


int TimeController::Update()
{
	// Get current system time
	clock_t _currentTime = clock();

	// Calculate the frametime for this update
	currentFrametime = ((int)_currentTime - lastUpdateTime);

	// Last update time is now
	lastUpdateTime = _currentTime;

	return 1;
}


int TimeController::GetMoveDistanceForSpeed(int _speed)
{
	return (_speed*currentFrametime) / 10;
}


int TimeController::GetRotateDistanceForSpeed(int _speed)
{
	return (_speed*currentFrametime) / 40;
}


TimeController* TimeController::Instance()
{
	if (!t_instance)
	{
		t_instance = new TimeController();
	}
	return t_instance;
}