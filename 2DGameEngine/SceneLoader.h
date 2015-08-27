#ifndef SCENELOADER_H
#define SCENELOADER_H

#include "Scene.h"
#include "GamepadInputReciever.h"
#include "PcInputReciever.h"
#include "Position.h"
#include "Scene.h"
#include <string>

/// <summary>
/// The Scene Loader is used by the scene Factory to load scene files and read them.
/// </summary>
class SceneLoader
{
public:
	SceneLoader(GamepadInputReciever*, PcInputReciever*);
	~SceneLoader();

	/// <summary>
	/// Put entities in the given scene by reading its scene file.
	/// </summary>
	int LoadScene(Scene*);
private:

	/// <summary>
	/// Loads an entity from a file.
	/// </summary>
	int LoadEntity(std::string, Position*, Scene*);

	/// <summary>
	/// Converts a string of coordinates from the scene file to a Position object.
	/// </summary>
	Position* StringToPosition(std::string);

	/// <summary>
	/// Convert a string to a boolean
	/// </summary>
	bool StringToBoolean(std::string);

	/// <summary>
	/// Convert a string to an int
	/// </summary>
	int StringToInt(std::string);

	GamepadInputReciever* GamepadReciever;
	PcInputReciever* PcReciever;
};

#endif