#include "Scene.h"


Scene::Scene(std::string _name)
{
	Name = _name;
	NumberOfEntities = 0;
}


Scene::~Scene()
{
}


int Scene::AddEntity(Entity* _entity)
{
	if (NumberOfEntities == MAX_ENTITIES) return 0;
	InhabitingEntities[NumberOfEntities] = _entity;
	++NumberOfEntities;
	return 1;
}


Entity* Scene::GetEntity(int _index)
{
	if (_index == MAX_ENTITIES) return 0;
	return InhabitingEntities[_index];
}


int Scene::EntityCount()
{
	return NumberOfEntities;
}


std::string Scene::GetName()
{
	return Name;
}