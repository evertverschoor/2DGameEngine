#ifndef BATMAN_H
#define BATMAN_H

#include "Entity.h"
#include "PcInputHandler.h"

class Batman : public Entity, public PcInputHandler
{
public:
	Batman();
	~Batman();

	int HandleMouseInput(MouseState*);
	int HandleKeyboardInput(KeyboardState*);
};

#endif