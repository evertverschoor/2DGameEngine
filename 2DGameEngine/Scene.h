#define MAX_ENTITIES 64
#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include <string>

/// <summary>
/// A scene is a space in which entities exist, a scene is drawn to the screen by the renderer.
/// </summary>
class Scene
{
public:
	Scene(std::string);
	~Scene();

	/// <summary>
	/// Add an entity to the scene.
	/// </summary>
	int AddEntity(Entity*);

	/// <summary>
	/// Returns the entity that is located at the given index in the list.
	/// </summary>
	Entity* GetEntity(int);

	/// <summary>
	/// Returns how many entities exist in the scene currently.
	/// </summary>
	int EntityCount();

	std::string GetName();
protected:
	Entity* InhabitingEntities[MAX_ENTITIES];
private:
	int NumberOfEntities;
	std::string Name;
};

#endif