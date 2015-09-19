#ifndef BATMAN_H
#define BATMAN_H

#include "Entity.h"
#include "PcInputHandler.h"
#include "GamepadInputHandler.h"

class Batman : public Entity, public PcInputHandler, public GamepadInputHandler
{
public:
	Batman();
	~Batman();

	int Act();

	int HandleMouseInput(MouseState*);
	int HandleKeyboardInput(KeyboardState*);
	int HandleGamepadInput(GamepadState*);
	int GetGamepadNumber();

private:
	int MoveFromInput(bool, bool, bool, bool);
};

#endif