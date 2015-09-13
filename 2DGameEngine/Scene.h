#define MAX_ENTITIES 64
#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include "Dimension.h"
#include <string>

/// <summary>
/// A scene is a space in which entities exist, a scene is drawn to the screen by the renderer.
/// </summary>
class Scene
{
public:
	/// <summary>
	/// @param1 The scene name.
	/// @param2 The size of the scene in pixels (according to the virtual resolution).
	/// </summary>
	Scene(std::string, Dimension*);
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

	/// <summary>
	/// Returns the scene name.
	/// </summary>
	std::string GetName();

	/// <summary>
	/// Returns the scene size.
	/// </summary>
	Dimension* GetSize();

	/// <summary>
	/// Call Act() on all entities in the scene.
	/// </summary>
	int OnGameUpdate();
protected:
	/// <summary>
	/// A list of all the entities that are in the scene.
	/// </summary>
	Entity* inhabitingEntities[MAX_ENTITIES];
private:
	int numberOfEntities;
	std::string name;
	Dimension* size;
};

#endif