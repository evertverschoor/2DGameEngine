#ifndef PCINPUTHANDLER_H
#define PCINPUTHANDLER_H

#include "KeyboardState.h"
#include "MouseState.h"

/// <summary>
/// A gamepad input handler will recieve all the gamepad input and can act depending on what input is read.
/// </summary>
class PcInputHandler
{
public:
	virtual ~PcInputHandler() {};

	/// <summary>
	/// Do something with the keyboard state here.
	/// </summary>
	virtual int HandleKeyboardInput(KeyboardState*) = 0;

	/// <summary>
	/// Do something with the mouse state here.
	/// </summary>
	virtual int HandleMouseInput(MouseState*) = 0;
};

#endif