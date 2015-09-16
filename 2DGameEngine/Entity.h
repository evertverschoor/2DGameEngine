#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"
#include "Dimension.h"
#include <string>

/// <summary>
/// An entity is an object that exists in a scene, entities are drawn one by one by the renderer.
/// </summary>
class Entity
{
public:
	Entity();
	~Entity();

	/// <summary>
	/// Main function that is constantly called if this entity is in the active scene.
	/// </summary>
	virtual int Act() = 0;

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
	/// Set the direction for the entity, from 0-360. (degrees)
	/// </summary>
	int SetDirection(int);

	/// <summary>
	/// Get the direction the entity is facing, from 0-360. (degrees)
	/// </summary>
	int GetDirection();

	/// <summary>
	/// Get the speed the entity moves at.
	/// </summary>
	int GetSpeed();

	/// <summary>
	/// Returns the entity's hitbox.
	/// </summary>
	Dimension* GetHitbox();

	/// <summary>
	/// Returns if the entity may phase through other entities.
	/// </summary>
	bool IsPhased();

protected:
	/// <summary>
	/// Set the speed the entity will move at.
	/// </summary>
	int SetSpeed(int);

	/// <summary>
	/// Set the entity asset location.
	/// </summary>
	int SetAssetURI(std::string);

	/// <summary>
	/// Set the entity hitbox width and height.
	/// </summary>
	int SetHitbox(int, int);

	/// <summary>
	/// Can the entity phase through other objects?
	/// </summary>
	int SetPhaseState(bool);

private:
	Position entityPosition;
	Dimension hitBox;

	std::wstring assetURI;
	int direction;
	int speed;
	bool phased;
};

#endif