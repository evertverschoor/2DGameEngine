#include "Gravity.h"


Gravity::Gravity()
{
	SetDirection(SOUTH);
	SetIntensity(0);
}


Gravity::~Gravity()
{
}


int Gravity::GetIntensity()
{
	return intensity;
}


int Gravity::SetIntensity(int _value)
{
	if (_value >= 0)
	{
		intensity = _value;
		return 1;
	}
	else
	{
		return 0;
	}
}


Direction Gravity::GetDirection()
{
	return direction;
}


int Gravity::SetDirection(Direction _value)
{
	direction = _value;
	return 1;
}