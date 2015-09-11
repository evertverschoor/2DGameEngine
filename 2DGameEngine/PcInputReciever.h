#define MAX_HANDLERS 8

#ifndef PCINPUTRECIEVER_H
#define PCINPUTRECIEVER_H

#include "PcInputHandler.h"
#include "KeyboardState.h"
#include "ConstantMouseState.h"
#include <Windows.h>
#include <Windowsx.h>
#include <map>

/// <summary>
/// The pc input reciever will listen to the keyboard and mouse and send its input in a proper format to all pc input handlers.
/// </summary>
class PcInputReciever
{
public:
	PcInputReciever();
	~PcInputReciever();

	/// <summary>
	/// Add an input handler that will recieve the keyboard and mouse input.
	/// </summary>
	int AddPcHandler(PcInputHandler*);

	/// <summary>
	/// Pass the keyboard and mouse input to the handlers right now.
	/// </summary>
	int ReadInput();

	/// <summary>
	/// Windows passes the keyboard state to this class through this function.
	/// </summary>
	int KeyPressed(WPARAM);

	/// <summary>
	/// Windows passes the keyboard state to this class through this function.
	/// </summary>
	int KeyReleased(WPARAM);

	/// <summary>
	/// Windows passes the mouse state to this class through this function.
	/// </summary>
	int MouseMoved(LPARAM);

	/// <summary>
	/// Windows passes the mouse state to this class through this function.
	/// </summary>
	int MouseButtonPressed(int);

	/// <summary>
	/// Windows passes the mouse state to this class through this function.
	/// </summary>
	int MouseButtonReleased(int);
private:
	PcInputHandler* handlerList[MAX_HANDLERS];
	int numberOfHandlers;

	KeyboardState* presentableKeyboardState;
	MouseState* presentableMouseState;
	
	std::map<int, bool> currentKeyboardMap;
	ConstantMouseState* currentMouseMap;

	int ClearKeyboardState();
	int ClearMouseState();
};

#endif