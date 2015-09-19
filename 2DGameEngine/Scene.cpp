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
	for (int i = 0; i < EntityCount(); ++i)
	{
		inhabitingEntities[i]->Act();
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


bool Scene::IsValidMove(int _xPos, int _yPos, Position* _entityPosition, Dimension* _entityHitbox)
{
	bool _returnValue = true;

	// For each entity in the scene
	for (int i = 0; i < numberOfEntities; ++i)
	{
		Position* _targetEntityPosition = inhabitingEntities[i]->GetPosition();
		Dimension* _targetEntityHitbox = inhabitingEntities[i]->GetHitbox();

		// That is not the same entity as the one querying
		if (!(_targetEntityPosition == _entityPosition))
		{
			// If there's a collision
			if ( 
				_xPos < _targetEntityPosition->X+ _targetEntityHitbox->width &&
				_xPos + _entityHitbox->width > _targetEntityPosition->X &&

				_yPos < _targetEntityPosition->Y + _targetEntityHitbox->height &&
				_yPos + _entityHitbox->height > _targetEntityPosition->Y
				)

			{
				// Move is not valid
				_returnValue = false;
			}
		}
	}

	return _returnValue;
}