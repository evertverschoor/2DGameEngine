#include "Entity.h"


Entity::Entity()
{
	SetSpeed(10);
	SetHitbox(100, 100);
	SetPhaseState(true);
}


Entity::~Entity()
{
}


Position* Entity::GetPosition()
{
	return &position;
}


int Entity::JumpTo(int _xPos, int _yPos)
{
	// Check for collisions
	if (!phased && !collisionDetector->IsValidMove(_xPos, _yPos, &position, &hitbox)) return 0;

	position.X = _xPos;
	position.Y = _yPos;

	return 1;
}


int Entity::Move(float _xJump, float _yJump)
{
	// Calculate the actual distance we should traverse based on the framerate
	int _actualDistance = TimeController::Instance()->GetMoveDistanceForSpeed(speed);

	// Jump to the target point, the X and Y jump values multiplied by the jump distance
	JumpTo(position.X + _actualDistance*_xJump, position.Y + _actualDistance*_yJump);

	return 1;
}


int Entity::SetZindex(int _zindex)
{
	position.Z = _zindex;
	return 1;
}


std::wstring Entity::GetCurrentAssetUri()
{
	return assetUriList[currentAsset];
}


std::wstring Entity::GetAssetUriByIndex(int _index)
{
	if (_index >= numberOfAssets) return NULL;

	return assetUriList[_index];
}


int Entity::AssetCount()
{
	return numberOfAssets;
}


int Entity::AddAsset(std::string _key, std::string _uri)
{
	if (numberOfAssets == MAX_ASSETS) return 0;

	assetUriList[numberOfAssets] = StringConverter::Instance()->StringToWstring(_uri);
	assetMap[_key] = numberOfAssets;
	++numberOfAssets;

	return 1;
}


int Entity::SetCurrentAsset(std::string _key)
{
	currentAsset = assetMap[_key];
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


int Entity::Rotate(int _value)
{
	return SetDirection(direction + TimeController::Instance()->GetRotateDistanceForSpeed(_value));
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
	return &hitbox;
}


int Entity::SetHitbox(int _width, int _height)
{
	hitbox.width = _width;
	hitbox.height = _height;

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


int Entity::SetCollisionDetector(CollisionDetector* _detector)
{
	collisionDetector = _detector;
	return 1;
}