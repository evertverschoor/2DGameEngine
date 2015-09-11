#ifndef CONTROLLABLEENTITY_H
#define CONTROLLABLEENTITY_H

#include "Entity.h"
#include "GamepadInputHandler.h"
#include "PcInputHandler.h"
#include "GamepadState.h"
#include "MouseState.h"
#include "KeyboardState.h"

/// <summary>
/// A controllable entity implements gamepad and pc input handlers and can be controlled.
/// </summary>
class ControllableEntity : public Entity, public GamepadInputHandler, public PcInputHandler
{
public:
	ControllableEntity(std::string _uri, int _gamepadno) : Entity(_uri)
	{
		gamepadNumber = _gamepadno;
	};

	ControllableEntity(std::string _uri) : Entity(_uri)
	{
		gamepadNumber = 0;
	};

	ControllableEntity();
	~ControllableEntity();

	int GetGamepadNumber();
	int HandleGamepadInput(GamepadState*);
	int HandleKeyboardInput(KeyboardState*);
	int HandleMouseInput(MouseState*);
private:
	int gamepadNumber;
};

#endif