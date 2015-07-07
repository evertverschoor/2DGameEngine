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
	std::string _scenestring = FileReader::Instance()->ReadFile(_scene->GetName());
	DissectString(_scenestring, _scene);
	return 1;
}


int SceneLoader::DissectString(std::string _scenestring, Scene* _scene)
{
	#define MAX_STRINGS 80 // The max number of lines a scene file may contain
	std::string _strings[MAX_STRINGS];
	std::string _delimiter = "=";

	// --
	// This algorithm puts the scene file content into a string array
	// --
	int i = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = _scenestring.find(_delimiter)) != std::string::npos) {
		token = _scenestring.substr(0, pos);
		_strings[i] = token;
		++i;
		_scenestring.erase(0, pos + _delimiter.length());
	}

	// --
	// This algorithm reads entity properties from the string array and creates entities
	// --
	int a = 0;
	while (a<MAX_STRINGS)
	{
		// Found a new entity
		if (_strings[a] == "{")
		{
			// Grab the asset URI
			std::string _uri = _strings[a + 2];

			// Grab the position
			Position* _position = StringToPosition(_strings[a + 4]);

			// Grab the controllable value
			bool _controllable = StringToBoolean(_strings[a + 6]);

			// Create the entity with these properties
			if (_controllable)
			{
				// If controllable, grab the gamepad number
				int _gamepadno = StringToInt(_strings[a + 8]); 
				ControllableEntity* _entity = new ControllableEntity(_uri, _gamepadno-1);

				// Add the entity as a gamepad reciever if there is a gamepad and the entity's gamepad number is not 0
				if((GamepadReciever) && _gamepadno != 0) GamepadReciever->AddGamepadHandler(_entity); 

				// Add it as a pc reciever always
				PcReciever->AddPcHandler(_entity);

				_entity->JumpTo(_position->X, _position->Y);
				_entity->SetZindex(_position->Z);
				_scene->AddEntity(_entity);
			}
			else
			{
				Entity* _entity = new Entity(_uri);
				_entity->JumpTo(_position->X, _position->Y);
				_entity->SetZindex(_position->Z);
				_scene->AddEntity(_entity);
			}
		}
		++a;
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