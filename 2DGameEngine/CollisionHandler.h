#ifndef COLLISIONHANDLER_H
#define COLLISIONHANDLER_H

#include "Entity.h"

/// <summary>
/// A collision handler wants to do something with the entity it collides with.
/// </summary>
class CollisionHandler
{
public:
	virtual ~CollisionHandler() {};

	/// <summary>
	/// Handle a collision with another entity.
	/// </summary>
	virtual int HandleCollision(Entity*) = 0;
};

#endif