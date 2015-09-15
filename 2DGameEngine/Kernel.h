// The number of frames that are saved before the average framerate is calculated.
// A higher number results in slower update rate on lower Hz monitors.
// I.E. 60 will result in an update each second on a 60Hz monitor.
#define FRAMES_MEASURED 30

#ifndef KERNEL_H
#define KERNEL_H

#include "Window.h"
#include "Renderer.h"
#include "Scene.h"
#include "VideoSettings.h"
#include "Logger.h"
#include "AssetManager.h"
#include "GamepadInputReciever.h"
#include "PcInputReciever.h"
#include "GFXController.h"
#include "DirectXRenderer.h"
#include "DirectXAssetManager.h"
#include "XInputReciever.h"
#include "AudioEngine.h"
#include "AudioPlayer.h"
#include "AudioManager.h"
#include "XAudio2Player.h"
#include "XAudio2Manager.h"
#include "Camera.h"
#include <thread>

// The default virtual resolution is this, if the first constructor is called.
#define DEFAULT_VIRTUAL_RESOLUTION_WIDTH 1920
#define DEFAULT_VIRTUAL_RESOLUTION_HEIGHT 1080

/// <summary>
/// The kernel is the starting point for the engine.
/// </summary>
class Kernel
{
public:
	/// <summary>
	/// @param1 The hInstance that is passed as a parameter from WinMain needs to be passed along.
	/// </summary>
	Kernel(HINSTANCE*);

	/// <summary>
	/// @param1 The hInstance that is passed as a parameter from WinMain needs to be passed along.
	/// @param2 The virtual resolution width.
	/// @param3 The virtual resolution height.
	/// </summary>
	Kernel(HINSTANCE*, int, int);

	~Kernel();

	/// <summary>
	/// Initialize the engine.
	/// @param The text the game window will display.
	/// </summary>
	int Init(LPCWSTR);

	/// <summary>
	/// The engine will run when this function is called, and the game loop is entered.
	/// The game loop can only be stopped in-game or by closing the primary window.
	/// </summary>
	int Run();

	/// <summary>
	/// Set the way the camera moves. The default is NORMAL.
	/// </summary>
	int SetCameraMovement(CameraMovement);

	/// <summary>
	/// Get a copy of the asset manager to load all the assets in a scene.
	/// </summary>
	AssetManager* GetAssetManager();

	/// <summary>
	/// Get a copy of the pc input reciever to make entities pc input handlers.
	/// </summary>
	PcInputReciever* GetPcInputReciever();

	/// <summary>
	/// Get a copy of the gamepad input reciever to make entities gamepad input handlers.
	/// </summary>
	GamepadInputReciever* GetGamepadInputReciever();

	/// <summary>
	/// Start a scene that has its assets loaded by the asset manager.
	/// </summary>
	int StartScene(Scene*);

	/// <summary>
	/// Returns whether or not the engine is ready to be used.
	/// </summary>
	bool Ready();

private:
	Window* mainWindow;
	Renderer* gameRenderer;
	Camera* camera;

	GamepadInputReciever* gamepadReciever;
	PcInputReciever* pcReciever;

	AssetManager* resourceManager;
	Scene* activeScene;

	AudioEngine* audioEngine;
	AudioPlayer* audioPlayer;
	AudioManager* audioManager;

	VideoSettings* vSettings;
	Logger* log;
	GFXController* gfx;
	HINSTANCE* hInstance;

	Dimension virtualResolution;

	bool ready;

	// Objects for measuring the framerate.
	clock_t lastFrameTime;
	float frametimeList[FRAMES_MEASURED];
	int numberOfFramesMeasured;

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
	/// Calculate the current frametime, and if enough frametimes have been saved, calculate the framerate.
	/// </summary>
	int CalculateCurrentFramerate();

	/// <summary>
	/// Show the engine splash screen so long as there is no active scene.
	/// </summary>
	int ShowEngineSplash();
};

#endif