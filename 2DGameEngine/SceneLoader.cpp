#include "SceneLoader.h"
#include "FileReader.h"
#include "Logger.h"
#include "Entity.h"
#include "ControllableEntity.h"
#include "Windows.h"
#include "Position.h"
#include <string>


SceneLoader::SceneLoader(GamepadInputReciever* _gamepadreciever, PcInputReciever* _pcreciever)
{
	GamepadReciever = _gamepadreciever;
	PcReciever = _pcreciever;
}


SceneLoader::~SceneLoader()
{
	delete GamepadReciever;
	delete PcReciever;
}


int SceneLoader::LoadScene(Scene* _scene)
{
	std::string _sceneString = FileReader::Instance()->ReadFile(_scene->GetName());

	// Iterate through each entity
	while (_sceneString.length() != 0) 
	{

		int _endOfEntityName = _sceneString.find("(");
		std::string _entityName = _sceneString.substr(0, _endOfEntityName);

		std::string _positionString = _sceneString.substr(_sceneString.find("(") + 1, _sceneString.find(")") - _sceneString.find("(") - 1);

		LoadEntity(_entityName, StringToPosition(_positionString), _scene);

		_sceneString.erase(0, _sceneString.find(";") + 1);
	}

	return 1;
}

int SceneLoader::LoadEntity(std::string _entityName, Position* _position, Scene* _scene)
{
	std::string _entityString = FileReader::Instance()->ReadFile("Data/Entities/" + _entityName + ".entity");

	std::string _assetURI = _entityString.substr(10, _entityString.find(";") - 11);
	
	std::string _controllableAsString = _entityString.substr(_entityString.find("Controllable") + 13, 1);
	bool _controllable = StringToBoolean(_controllableAsString);

	// Assign a gamepad if controllable
	if (_controllable)
	{
		// Gamepad number is 1 always
		int _gamepadno = 1;
		ControllableEntity* _entity = new ControllableEntity(_assetURI, _gamepadno - 1);

		// Add the entity as a gamepad reciever if there is a gamepad and the entity's gamepad number is not 0
		if ((GamepadReciever) && _gamepadno != 0) GamepadReciever->AddGamepadHandler(_entity);

		// Add it as a pc reciever always
		PcReciever->AddPcHandler(_entity);

		_entity->JumpTo(_position->X, _position->Y);
		_entity->SetZindex(_position->Z);
		_scene->AddEntity(_entity);
	}
	else
	{
		Entity* _entity = new Entity(_assetURI);
		_entity->JumpTo(_position->X, _position->Y);
		_entity->SetZindex(_position->Z);
		_scene->AddEntity(_entity);
	}

	return 1;
}


Position* SceneLoader::StringToPosition(std::string _string)
{
	int _positions[3];
	std::string _delimiter = ",";

	int i = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = _string.find(_delimiter)) != std::string::npos) {
		token = _string.substr(0, pos);
		_positions[i] = std::stoi(token);
		++i;
		_string.erase(0, pos + _delimiter.length());
	}

	return new Position(_positions[0], _positions[1], _positions[2]);
}


bool SceneLoader::StringToBoolean(std::string _string)
{
	return (_string == "1") ? true : false;
}


int SceneLoader::StringToInt(std::string _string)
{
	return std::stoi(_string);
}