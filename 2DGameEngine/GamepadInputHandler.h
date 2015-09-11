#ifndef GAMEPADINPUTHANDLER_H
#define GAMEPADINPUTHANDLER_H

#include "GamepadState.h"

/// <summary>
/// A gamepad input handler will recieve all the gamepad input and can act depending on what input is read.
/// </summary>
class GamepadInputHandler
{
public:
	virtual ~GamepadInputHandler() {};

	/// <summary>
	/// Do something wth the gamepad state, the controller will vibrate depending on what is returned.
	/// Return 1 to vibrate LEFT
	/// Return 2 to vibrate RIGHT
	/// Return 3 to vibrate BOTH
	/// Return 0 to not vibrate
	/// </summary>
	virtual int HandleGamepadInput(GamepadState*) = 0;

	/// <summary>
	/// Returns the gamepad number this entity is responding to.
	/// </summary>
	virtual int GetGamepadNumber() = 0;
};

#endif