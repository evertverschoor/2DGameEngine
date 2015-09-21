#include "Ground.h"


Ground::Ground()
{
	AddAsset("main", "Assets/UI/ArkhamKnight.jpg");
	SetCurrentAsset("main");
	SetHitbox(2000, 100);
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