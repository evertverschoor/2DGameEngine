#include "Scene.h"


Scene::Scene()
{
	numberOfEntities = 0;
}


Scene::~Scene()
{
}

int Scene::OnGameUpdate()
{
	int _momentumIncrease = TimeController::Instance()->GetMomentumIncrease(gravity.GetIntensity());

	for (int i = 0; i < EntityCount(); ++i)
	{
		Entity* _entity = inhabitingEntities[i];

		// Set entity momentum if not floating
		if (!_entity->Floating())
		{
			_entity->SetMomentum(_momentumIncrease, gravity.GetDirection());
			_entity->Fall();
		}

		// Act() on entity
		_entity->Act();
	}

	return 1;
}


int Scene::AddEntity(Entity* _entity)
{
	if (numberOfEntities == MAX_ENTITIES) return 0;
	_entity->SetCollisionDetector(this);
	inhabitingEntities[numberOfEntities] = _entity;
	++numberOfEntities;

	return 1;
}


Entity* Scene::GetEntity(int _index)
{
	if (_index == MAX_ENTITIES) return 0;

	return inhabitingEntities[_index];
}


int Scene::EntityCount()
{
	return numberOfEntities;
}


std::string Scene::GetName()
{
	return name;
}


Dimension* Scene::GetSize()
{
	return size;
}


int Scene::SetName(std::string _value)
{
	name = _value;
	return 1;
}


int Scene::SetSize(Dimension* _value)
{
	size = _value;
	return 1;
}


int Scene::SetBackgroundAssetURI(std::string _value)
{
	std::wstring _assetURI(_value.begin(), _value.end());
	backgroundAssetURI = _assetURI;

	return 1;
}


std::wstring Scene::GetBackgroundAssetURI()
{
	return backgroundAssetURI;
}


int Scene::SetBackgroundType(BackgroundType _value)
{
	backgroundType = _value;
	return 1;
}


BackgroundType* Scene::GetBackgroundType()
{
	return &backgroundType;
}


int Scene::OrderByZIndex()
{
	Entity* _newList[MAX_ENTITIES];

	for (int i = 0; i < numberOfEntities; ++i)
	{
		int _lowestZIndex = 1000;

		int _winner = 0;

		for (int j = 0; j < numberOfEntities; ++j)
		{
			if (inhabitingEntities[j] != NULL && inhabitingEntities[j]->GetPosition()->Z < _lowestZIndex)
			{
				_winner = j;
				_lowestZIndex = inhabitingEntities[j]->GetPosition()->Z;
			}
		}

		_newList[i] = inhabitingEntities[_winner];
		inhabitingEntities[_winner] = NULL;
	}

	for (int i = 0; i < numberOfEntities; ++i)
	{
		inhabitingEntities[i] = _newList[i];
	}

	return 1;
}


int Scene::SetGravityDirection(Direction _value)
{
	gravity.SetDirection(_value);
	return 1;
}


int Scene::SetGravityIntensity(int _value)
{
	gravity.SetIntensity(_value);
	return 1;
}


bool Scene::DetectCollision(int* _xPos, int* _yPos, Entity* _queryingEntity)
{
	bool _returnValue = true;

	// Define querying entity position and hitbox
	Position* _entityPosition = _queryingEntity->GetPosition();
	Dimension* _entityHitbox = _queryingEntity->GetHitbox();

	// For each entity in the scene
	for (int i = 0; i < numberOfEntities; ++i)
	{
		// Define target entity position and hitbox
		Entity* _targetEntity = inhabitingEntities[i];
		Position* _targetEntityPosition = _targetEntity->GetPosition();
		Dimension* _targetEntityHitbox = _targetEntity->GetHitbox();

		// Make sure entity is not the same entity as the one querying and is not phased
		if (!_targetEntity->IsPhased() && !(_targetEntityPosition == _entityPosition))
		{
			// If there's a collision
			if ( 
				*_xPos < _targetEntityPosition->X + _targetEntityHitbox->width &&
				*_xPos + _entityHitbox->width > _targetEntityPosition->X &&

				*_yPos < _targetEntityPosition->Y + _targetEntityHitbox->height &&
				*_yPos + _entityHitbox->height > _targetEntityPosition->Y
				)
			{
				// --------------------------------------------------------------
				// Store the closest valid move in the first two given parameters
				// --------------------------------------------------------------

				// Calculate which direction the entity came from
				int _deltaX = (_entityPosition->X + _entityHitbox->width) - _targetEntityPosition->X;
				int _deltaY = (_entityPosition->Y + _entityHitbox->height) - _targetEntityPosition->Y;

				// Came from the left
				if (_deltaX <= 0 && _deltaX < _deltaY)
				{
					*_xPos = _targetEntityPosition->X - _entityHitbox->width;
				}

				// Came from the top
				else if (_deltaY <= 0 && _deltaY < _deltaX)
				{
					*_yPos = _targetEntityPosition->Y - _entityHitbox->height;
				}

				// Came from the right
				else if (_deltaX > 0 && _deltaX > _deltaY)
				{
					*_xPos = _targetEntityPosition->X + _targetEntityHitbox->width;
				}

				// Came from the bottom
				else if (_deltaY > 0 && _deltaY > _deltaX)
				{
					*_yPos = _targetEntityPosition->Y + _targetEntityHitbox->height;
				}

				// Call HandleCollision() on the querying entity, passing the target entity along
				_queryingEntity->HandleCollision(_targetEntity);

				_returnValue = false;
			}
		}
	}

	return _returnValue;
}