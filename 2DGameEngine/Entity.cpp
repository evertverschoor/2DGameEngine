#include "Entity.h"


Entity::Entity(std::string _uri)
{
	assetURI = _uri;
	JumpTo(0, 0);
	SetDirection(0);
	SetSpeed(10);
}


Entity::Entity()
{
}


Entity::~Entity()
{
}

int Entity::Act()
{
	return 1;
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
	std::wstring _returnValue(assetURI.begin(), assetURI.end());
	return _returnValue;
}


int Entity::SetAsssetURI(std::string _value)
{
	assetURI = _value;
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