#include "Ground.h"


Ground::Ground()
{
	AddAsset("main", "Assets/Environment/Ground.png");
	SetCurrentAsset("main");
	SetHitbox(3840, 100);
	SetSpeed(0);
	SetPhaseState(false);
	SetFloatState(true);
}


Ground::~Ground()
{
}


int Ground::Act()
{
	return 1;
}


int Ground::HandleCollision(Entity* _entity)
{
	return 1;
}


int Ground::Tell(int)
{
	return 1;
}