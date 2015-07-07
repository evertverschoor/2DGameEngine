#ifndef WINDOW_H
#define WINDOW_H

#include "Windows.h"
#include "VideoSettings.h"
#include "PcInputReciever.h"

/// <summary>
/// A window is used by the renderer to draw on.
/// </summary>
class Window
{
public:
	/// <summary>
	/// @param1 The name of the window that will show in the window chrome.
	/// @param2 The hInstance that should be saved in the kernel.
	/// @param3 The pc input reciever to pass the keyboard and mouse input to.
	/// </summary>
	Window(LPCWSTR, HINSTANCE*, PcInputReciever*);
	~Window();

	/// <summary>
	/// Set the window settings.
	/// </summary>
	int SetVideoSettings(VideoSettings*);

	/// <summary>
	/// Launch the window.
	/// </summary>
	int Launch();

	/// <summary>
	/// Returns whether or not the window is still up.
	/// </summary>
	bool IsUp();

	/// <summary>
	/// The actual C++ window handle.
	/// </summary>
	HWND Handle;

private:
	VideoSettings* Settings;
	PcInputReciever* PcReciever;
	bool WindowIsUp;
	LPCWSTR Name;
	HINSTANCE* hInstance;
};

#endif