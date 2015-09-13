#include "SceneFactory.h"


SceneFactory::SceneFactory(AssetManager* _assetmanager, GamepadInputReciever* _gamepadreciever, PcInputReciever* _pcreciever)
{
	resourceManager = _assetmanager;
	loader = new SceneLoader(_gamepadreciever, _pcreciever);
	numberOfScenes = 0;
}


SceneFactory::~SceneFactory()
{
	delete loader;
	delete resourceManager;
}


Scene* SceneFactory::CreateNewSceneFromFile(std::string _name)
{
	Logger::Instance()->Log("\n\nCreating new Scene from file: ");
	Logger::Instance()->Log(_name);

	if (numberOfScenes == MAX_SCENES)
	{
		Logger::Instance()->Log("\nCould not create another scene, too many scenes already exist.");
		return 0;
	}

	Scene* _newScene = new Scene(_name, new Dimension(3840,2160));
	createdScenes[numberOfScenes] = _newScene;
	++numberOfScenes;

	// Put the entities in the scene
	loader->LoadScene(_newScene);

	// Load the assets that are required to draw the scene
	resourceManager->LoadScene(_newScene);

	Logger::Instance()->Log("\nDone creating scene.");

	return _newScene;
}


Scene* SceneFactory::GetScene(int _index)
{
	if (_index == numberOfScenes) return 0;
	return createdScenes[_index];
}