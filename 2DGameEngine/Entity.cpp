#include "Entity.h"
#include "Windows.h"
#include "Logger.h"
#include <string>


Entity::Entity(std::string _uri)
{
	AssetURI = _uri;
	JumpTo(0, 0);
	SetDirection(0);
}


Entity::Entity()
{
}


Entity::~Entity()
{
}


Position Entity::GetPosition()
{
	return EntityPosition;
}


int Entity::JumpTo(double _xPos, double _yPos)
{
	EntityPosition.X = _xPos;
	EntityPosition.Y = _yPos;
	return 1;
}


int Entity::SetZindex(double _zindex)
{
	EntityPosition.Z = _zindex;
	return 1;
}


std::wstring Entity::GetAssetURI()
{
	std::wstring _returnValue(AssetURI.begin(), AssetURI.end());
	return _returnValue;
}


int Entity::GetDirection()
{
	return Direction;
}


int Entity::SetDirection(int _value)
{
	if (_value >= 0 && _value < 361)
	{
		Direction = _value;
	}
	else if (_value < 0)
	{
		SetDirection(360 + _value);
	}
	else if (_value > 360)
	{
		SetDirection(_value - 360);
	}
	return Direction;
}