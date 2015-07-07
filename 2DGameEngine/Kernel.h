#ifndef KERNEL_H
#define KERNEL_H

#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneFactory.h"
#include "Windows.h"
#include "VideoSettings.h"
#include "Logger.h"
#include "AssetManager.h"
#include "GamepadInputReciever.h"
#include "PcInputReciever.h"

/// <summary>
/// The kernel is the starting point for the engine.
/// </summary>
class Kernel
{
public:
	/// <summary>
	/// The hInstance that is passed as a parameter from WinMain needs to be passed along.
	/// </summary>
	Kernel(HINSTANCE*);
	~Kernel();

	/// <summary>
	/// The engine will run when this function is called, and the game loop is entered.
	/// The game loop can only be stopped in-game or by closing the primary window.
	/// </summary>
	int Run();

private:
	Window* MainWindow;
	Renderer* GameRenderer;
	GamepadInputReciever* GamepadReciever;
	PcInputReciever* PcReciever;
	SceneFactory* SceneManager;
	AssetManager* ResourceManager;
	Scene* ActiveScene;
	VideoSettings* VSettings;
	Logger* Log;
	HINSTANCE* hInstance;

	/// <summary>
	/// Set up a demo scene so the engine is ready-to-use.
	/// </summary>
	int SetupDemoScene();

	/// <summary>
	/// This function is called continuously by the game loop.
	/// This means everything this function does will happen about 60 times a second, give or take.
	/// </summary>
	int OnGameUpdate();

	/// <summary>
	/// Mark the start of a new session in the log file.
	/// </summary>
	int LogNewSession();

	/// <summary>
	/// Tells whether or not there's still an active window, this is so the kernel shuts off when the window is closed.
	/// </summary>
	bool Running();

	int SetActiveScene(Scene*);
};

#endif