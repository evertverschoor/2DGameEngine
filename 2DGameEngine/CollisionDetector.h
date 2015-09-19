#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "Position.h"
#include "Dimension.h"

class CollisionDetector
{
public:
	virtual ~CollisionDetector() {};

	/// <summary>
	/// Returns whether or not the given coordinates do not collide with another entity,
	/// assuming the given position and hitbox belong to the querying entity.
	/// </summary>
	virtual bool IsValidMove(int, int, Position*, Dimension*) = 0;
};

#endif