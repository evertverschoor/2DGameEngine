#ifndef ENTITY_H
#define ENTITY_H

#include "Position.h"
#include "Dimension.h"
#include "TimeController.h"
#include "StringConverter.h"
#include "CollisionDetector.h"
#include "Entity.h"
#include "Direction.h"
#include <string>
#include <map>

#define MAX_ASSETS 50

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
	/// Handle a collision with another entity.
	/// </summary>
	virtual int HandleCollision(Entity*) = 0;

	/// <summary>
	/// Put the entity at a new x-y position.
	/// </summary>
	int JumpTo(int, int);

	/// <summary>
	/// Set the depth that the entity is located at.
	/// </summary>
	int SetZindex(int);

	/// <summary>
	/// Get the position of the entity as a Position object.
	/// </summary>
	Position* GetPosition();

	/// <summary>
	/// Get the Uri of the asset that will currently be displayed.
	/// </summary>
	std::wstring GetCurrentAssetUri();

	/// <summary>
	/// Get the asset uri that belongs to this index.
	/// </summary>
	std::wstring GetAssetUriByIndex(int);

	/// <summary>
	/// Get the number of assets this entity has.
	/// </summary>
	int AssetCount();

	/// <summary>
	/// Set the direction for the entity, from 0-360. (degrees)
	/// </summary>
	int SetDirection(int);

	/// <summary>
	/// Adjust the direction of the entity by a value.
	/// </summary>
	int Rotate(int);

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
	/// Returns if the entity may phase through other entities. (unaffected by collisions)
	/// </summary>
	bool IsPhased();

	/// <summary>
	/// Returns if the entity is unaffected by gravity.
	/// </summary>
	bool Floating();

	/// <summary>
	/// Set the entity momentum for gravitation
	/// @param1 How much to INCREASE the momentum by
	/// @param2 The direction of the momentum
	/// </summary>
	int SetMomentum(int, Direction);

	/// <summary>
	/// Fall into the momentum direction, with the momentum as speed
	/// </summary>
	int Fall();

	/// <summary>
	/// Set the collision detector to use whenever moving.
	/// </summary>
	int SetCollisionDetector(CollisionDetector*);

protected:
	/// <summary>
	/// Move a percentage of the speed into X and Y direction (so 1.0f is 100%)
	/// Use this to move instead of JumpTo, for framerate-independent movespeed.
	/// </summary>
	int Move(float, float);

	/// <summary>
	/// Set the speed the entity will move at.
	/// </summary>
	int SetSpeed(int);

	/// <summary>
	/// Add a new asset.
	/// @param1 The key for using the asset Uri during runtime.
	/// @param2 The asset Uri.
	/// </summary>
	int AddAsset(std::string, std::string);

	/// <summary>
	/// Set a new asset to be drawn by the renderer.
	/// @param The asset key.
	/// </summary>
	int SetCurrentAsset(std::string);

	/// <summary>
	/// Set the entity hitbox width and height.
	/// </summary>
	int SetHitbox(int, int);

	/// <summary>
	/// Can the entity phase through other objects?
	/// </summary>
	int SetPhaseState(bool);

	/// <summary>
	/// Is the entity unaffected by gravity?
	/// </summary>
	int SetFloatState(bool);

private:
	Position position;
	Dimension hitbox;

	CollisionDetector* collisionDetector;

	// Asset Uri's are stored in a list here
	std::wstring assetUriList[MAX_ASSETS];

	// Each asset is given a key, value points to the index of the list above
	std::map<std::string, int> assetMap;

	// Number of assets is kept track of
	int numberOfAssets;

	// Current asset that is to be drawn by the renderer, points to the index of assetUriList[]
	int currentAsset;

	int direction;
	int speed;

	// Gravity-related physics
	int momentum;
	Direction momentumDirection;

	bool phased;
	bool floating;
};

#endif