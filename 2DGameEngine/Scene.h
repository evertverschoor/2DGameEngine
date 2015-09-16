#define MAX_ENTITIES 64
#ifndef SCENE_H
#define SCENE_H

#include "Entity.h"
#include "Dimension.h"
#include "BackgroundType.h"
#include <string>

/// <summary>
/// A scene is a space in which entities exist, a scene is drawn to the screen by the renderer.
/// </summary>
class Scene
{
public:
	Scene();
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
	/// Returns the URI to the scene's background asset.
	/// </summary>
	std::wstring GetBackgroundAssetURI();

	/// <summary>
	/// Returns the background type of this scene.
	/// </summary>
	BackgroundType* GetBackgroundType();

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

	/// <summary>
	/// Set the scene name.
	/// </summary>
	int SetName(std::string);

	/// <summary>
	/// Set the scene size in pixels
	/// (keeping the virtual resolution in mind, so 2x the width of the virtual resolution is 2x the screen/window size)
	/// </summary>
	int SetSize(Dimension*);

	/// <summary>
	/// Set the URI to the scene background asset.
	/// </summary>
	int SetBackgroundAssetURI(std::string);

	/// <summary>
	/// Set the way the background behaves.
	/// </summary>
	int SetBackgroundType(BackgroundType);
private:
	int numberOfEntities;
	std::string name;
	std::wstring backgroundAssetURI;
	Dimension* size;
	BackgroundType backgroundType;
};

#endif