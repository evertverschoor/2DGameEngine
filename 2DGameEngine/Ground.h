#ifndef GROUND_H
#define GROUND_H

#include "Entity.h"

class Ground : public Entity
{
public:
	Ground();
	~Ground();

	int Act();
	int HandleCollision(Entity*);
};

#endif