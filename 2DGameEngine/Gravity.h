#ifndef GRAVITY_H
#define GRAVITY_H

#include "Direction.h"

/// <summary>
/// Gravity is a scene-wide factor that moves entities in a certain direction every time the game loops
/// </summary>
class Gravity
{
public:
	Gravity();
	~Gravity();

	/// <summary>
	/// Set the gravity direction (NORTH, EAST, SOUTH or WEST)
	/// </summary>
	int SetDirection(Direction);

	/// <summary>
	/// Set the gravity intensity
	/// </summary>
	int SetIntensity(int);

	/// <summary>
	/// Get the gravity direction.
	/// </summary>
	Direction GetDirection();

	/// <summary>
	/// Get the gravity intensity.
	/// </summary>
	int GetIntensity();
private:
	Direction direction;
	int intensity;
};

#endif