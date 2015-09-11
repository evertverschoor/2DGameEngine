#ifndef CONTROLLABLEENTITY_H
#define CONTROLLABLEENTITY_H

#include "Entity.h"
#include "GamepadInputHandler.h"
#include "PcInputHandler.h"
#include "GamepadState.h"
#include "MouseState.h"
#include "KeyboardState.h"
#include <Windows.h>
#include <Xinput.h>

class ControllableEntity : public Entity, public GamepadInputHandler, public PcInputHandler
{
public:
	ControllableEntity(std::string _uri, int _gamepadno) : Entity(_uri)
	{
		GamepadNumber = _gamepadno;
	};

	ControllableEntity(std::string _uri) : Entity(_uri)
	{
		GamepadNumber = 0;
	};

	ControllableEntity();
	~ControllableEntity();

	int GetGamepadNumber();

	/// <summary>
	/// Do something wth the gamepad state, the controller will vibrate depending on what is returned.
	/// Return 1 to vibrate LEFT
	/// Return 2 to vibrate RIGHT
	/// Return 3 to vibrate BOTH
	/// Return 0 to not vibrate
	/// </summary>
	int HandleGamepadInput(GamepadState*);

	int HandleKeyboardInput(KeyboardState*);
	int HandleMouseInput(MouseState*);
private:
	int GamepadNumber;
};

#endif