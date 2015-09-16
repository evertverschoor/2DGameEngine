#include "Scene.h"


Scene::Scene()
{
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