#define MAX_SCENES 8
#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

#include "Scene.h"
#include "AssetManager.h"
#include "SceneLoader.h"
#include "GamepadInputReciever.h"
#include "PcInputReciever.h"
#include "Logger.h"

/// <summary>
/// The Scene Factory is called upon whenever a new scene needs to be created and loaded for use.
/// </summary>
class SceneFactory
{
public:
	SceneFactory(AssetManager*, GamepadInputReciever*, PcInputReciever*);
	~SceneFactory();

	/// <summary>
	/// Creates a new scene from a given path to a Scene file.
	/// </summary>
	Scene* CreateNewSceneFromFile(std::string);

	/// <summary>
	/// Returns the scene that is located at the given index in the list.
	/// </summary>
	Scene* GetScene(int);
private:
	AssetManager* resourceManager;
	SceneLoader* loader;
	Scene* createdScenes[MAX_SCENES];
	int numberOfScenes;
};

#endif