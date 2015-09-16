#include "Entity.h"


Entity::Entity()
{
	JumpTo(0, 0);
	SetDirection(0);
	SetSpeed(10);
	SetHitbox(100, 100);
}


Entity::~Entity()
{
}


Position Entity::GetPosition()
{
	return entityPosition;
}


int Entity::JumpTo(double _xPos, double _yPos)
{
	entityPosition.X = _xPos;
	entityPosition.Y = _yPos;
	return 1;
}


int Entity::SetZindex(double _zindex)
{
	entityPosition.Z = _zindex;
	return 1;
}


std::wstring Entity::GetAssetURI()
{
	return assetURI;
}


int Entity::SetAssetURI(std::string _value)
{
	std::wstring _assetURI(_value.begin(), _value.end());
	assetURI = _assetURI;
	return 1;
}


int Entity::GetDirection()
{
	return direction;
}


int Entity::SetDirection(int _value)
{
	if (_value >= 0 && _value < 361)
	{
		direction = _value;
	}
	else if (_value < 0)
	{
		SetDirection(360 + _value);
	}
	else if (_value > 360)
	{
		SetDirection(_value - 360);
	}
	return direction;
}


int Entity::GetSpeed()
{
	return speed;
}


int Entity::SetSpeed(int _value)
{
	speed = _value >= 0 ? _value : speed;
	return 1;
}


Dimension* Entity::GetHitbox()
{
	return &hitBox;
}


int Entity::SetHitbox(int _width, int _height)
{
	hitBox.width = _width;
	hitBox.height = _height;

	return 1;
}


bool Entity::IsPhased()
{
	return phased;
}


int Entity::SetPhaseState(bool _value)
{
	phased = _value;
	return 1;
}