#include "SceneFactory.h"
#include "Scene.h"
#include "Entity.h"
#include "Logger.h"


SceneFactory::SceneFactory(AssetManager* _assetmanager, GamepadInputReciever* _gamepadreciever, PcInputReciever* _pcreciever)
{
	ResourceManager = _assetmanager;
	Loader = new SceneLoader(_gamepadreciever, _pcreciever);
	Log = Logger::Instance();
	NumberOfScenes = 0;
}


SceneFactory::~SceneFactory()
{
	delete Loader;
	delete Log;
	delete ResourceManager;
}


Scene* SceneFactory::CreateNewSceneFromFile(std::string _name)
{
	Log->Log("\n\nCreating new Scene from file: ");
	Log->Log(_name);

	if (NumberOfScenes == MAX_SCENES)
	{
		Log->Log("\nCould not create another scene, too many scenes already exist.");
		return 0;
	}

	Scene* _newScene = new Scene(_name);
	CreatedScenes[NumberOfScenes] = _newScene;
	++NumberOfScenes;

	// Put the entities in the scene
	Loader->LoadScene(_newScene);

	// Load the assets that are required to draw the scene
	ResourceManager->LoadScene(_newScene);

	Log->Log("\nDone creating scene.");

	return _newScene;
}


Scene* SceneFactory::GetScene(int _index)
{
	if (_index == NumberOfScenes) return 0;
	return CreatedScenes[_index];
}