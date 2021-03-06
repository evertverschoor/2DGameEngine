#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include "Scene.h"

/// <summary>
/// The Asset Manager is a non-directx resource manager that talks to the system.
/// </summary>
class AssetManager
{
public:
	virtual ~AssetManager() {};

	/// <summary>
	/// Tell the actual asset manager to load all the assets that belong to a scene.
	/// </summary>
	virtual int LoadScene(Scene*) = 0;

	/// <summary>
	/// Load a bitmap that doesnt belong to an entity.
	/// @param The bitmap uri.
	/// </summary>
	virtual int LoadSingleBitmap(std::string) = 0;
};

#endif