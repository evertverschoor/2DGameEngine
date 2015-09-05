#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"
#include "Windows.h"
#include <string>

/// <summary>
/// An entity is an object that exists in a scene, entities are drawn one by one by the renderer.
/// </summary>
class Entity
{
public:
	Entity(std::string);
	Entity();
	~Entity();

	/// <summary>
	/// Main function that is constantly called if this entity is in the active scene.
	/// </summary>
	int Act();

	/// <summary>
	/// Put the entity at a new x-y position.
	/// </summary>
	int JumpTo(double, double);

	/// <summary>
	/// Set the depth that the entity is located at.
	/// </summary>
	int SetZindex(double);

	/// <summary>
	/// Get the position of the entity as a Position object.
	/// </summary>
	Position GetPosition();

	/// <summary>
	/// Get the URI of the entity's asset for the asset loader.
	/// </summary>
	std::wstring GetAssetURI();

	int GetDirection();

	int SetDirection(int);

	int GetSpeed();

	int SetSpeed(int);
private:
	Position EntityPosition;
	std::string AssetURI;
	int Direction;
	int Speed;
};

#endif