#ifndef COLLISIONDETECTOR_H
#define COLLISIONDETECTOR_H

#include "Position.h"
#include "Dimension.h"

class Entity;

/// <summary>
/// A collision detector determines if a collision happens when an entity wants to move somewhere.
/// </summary>
class CollisionDetector
{
public:
	virtual ~CollisionDetector() {};

	/// <summary>
	/// Calculate if the target point collides with another entity,
	/// assumes the given position and hitbox belong to the querying entity.
	/// If a collion does take place, the closest position the entity may move is stored in the first two parameters.
	/// @param1 The X-coordinate to check for collisions
	/// @param2 The Y-coordinate to check for collisions
	/// @param3 The querying entity's current position
	/// @param4 The querying entity's hitbox
	/// @returns If the move was valid (false if there was a collision)
	/// </summary>
	virtual bool DetectCollision(int*, int*, Entity*) = 0;
};

#endif