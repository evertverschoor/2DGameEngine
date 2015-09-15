#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"
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

	/// <summary>
	/// Get the direction the entity is facing, from 0-360. (degrees)
	/// </summary>
	int GetDirection();

	/// <summary>
	/// Set the direction for the entity, from 0-360. (degrees)
	/// </summary>
	int SetDirection(int);

	/// <summary>
	/// Get the speed the entity moves at.
	/// </summary>
	int GetSpeed();

	/// <summary>
	/// Set the speed the entity will move at.
	/// </summary>
	int SetSpeed(int);

protected:
	int SetAsssetURI(std::string);

private:
	Position entityPosition;
	std::string assetURI;
	int direction;
	int speed;
};

#endif