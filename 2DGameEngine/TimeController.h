#ifndef TIMECONTROLLER_H
#define TIMECONTROLLER_H

#include "Windows.h"
#include "Logger.h"
#include <thread>

class TimeController
{
public:
	~TimeController();

	/// <summary>
	/// Signal a new gameloop has begun.
	/// </summary>
	int Update();

	/// <summary>
	/// Get framerate-independent move distance based on a speed value.
	/// </summary>
	int GetMoveDistanceForSpeed(int);

	/// <summary>
	/// Get framerate-independent rotate distance based on a speed value.
	/// </summary>
	int GetRotateDistanceForSpeed(int);

	/// <summary>
	/// Get the instance of the time controller using a static call.
	/// </summary>
	static TimeController* Instance();
private:
	TimeController() {};
	static TimeController* t_instance;

	int currentFrametime;
	clock_t lastUpdateTime;
};

#endif