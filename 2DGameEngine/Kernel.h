// The number of frames that are saved before the average framerate is calculated.
// A higher number results in slower update rate on lower Hz monitors.
// I.E. 60 will result in an update each second on a 60Hz monitor.
#define FRAMES_MEASURED 30

#ifndef KERNEL_H
#define KERNEL_H

#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include "SceneFactory.h"
#include "VideoSettings.h"
#include "Logger.h"
#include "AssetManager.h"
#include "GamepadInputReciever.h"
#include "PcInputReciever.h"
#include "GFXController.h"
#include "MotionBlurTestClass.h"
#include "DirectXRenderer.h"
#include "DirectXAssetManager.h"
#include "XInputReciever.h"
#include <thread>

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
	Window* mainWindow;
	Renderer* gameRenderer;
	GamepadInputReciever* gamepadReciever;
	PcInputReciever* pcReciever;
	SceneFactory* sceneManager;
	AssetManager* resourceManager;
	Scene* activeScene;
	VideoSettings* vSettings;
	Logger* log;
	GFXController* gfx;
	HINSTANCE* hInstance;

	// Objects for measuring the framerate.
	clock_t lastFrameTime;
	float frametimeList[FRAMES_MEASURED];
	int numberOfFramesMeasured;

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

	/// <summary>
	/// Set a new scene to be the currently active one and to be rendered.
	/// </summary>
	int SetActiveScene(Scene*);

	/// <summary>
	/// Calculate the current frametime, and if enough frametimes have been saved, calculate the framerate.
	/// </summary>
	int CalculateCurrentFramerate();
};

#endif