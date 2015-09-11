#define MAX_HANDLERS 8
#ifndef PCINPUTRECIEVER_H
#define PCINPUTRECIEVER_H

#include "PcInputHandler.h"
#include "KeyboardState.h"
#include "ConstantMouseState.h"
#include <Windows.h>
#include <map>

class PcInputReciever
{
public:
	PcInputReciever();
	~PcInputReciever();
	int AddPcHandler(PcInputHandler*);
	int ReadInput();
	int KeyPressed(WPARAM);
	int KeyReleased(WPARAM);
	int MouseMoved(LPARAM);
	int MouseButtonPressed(int);
	int MouseButtonReleased(int);
private:
	PcInputHandler* HandlerList[MAX_HANDLERS];
	int NumberOfHandlers;

	KeyboardState* PresentableKeyboardState;
	MouseState* PresentableMouseState;
	
	std::map<int, bool> CurrentKeyboardMap;
	ConstantMouseState* CurrentMouseMap;

	int ClearKeyboardState();
	int ClearMouseState();
};

#endif