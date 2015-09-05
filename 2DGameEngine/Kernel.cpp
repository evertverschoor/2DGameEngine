#include "Kernel.h"
#include "Window.h"
#include "Renderer.h"
#include "DirectXRenderer.h"
#include "Logger.h"
#include "DirectXAssetManager.h"
#include "XInputReciever.h"
#include <iostream>
#include <thread>
#include "Color.h"
#include "StringConverter.h"


Kernel::Kernel(HINSTANCE* _hInstance)
{
	Log = Logger::Instance();
	LogNewSession();

	// Set the hInstance
	hInstance = _hInstance;

	// Create the Gamepad Input Reciever as Xinput, if there are gamepads connected
	GamepadReciever = new XInputReciever();
	if (!GamepadReciever->HasGamepadsConnected()) GamepadReciever = NULL;

	// Create the Pc Input Reciever
	PcReciever = new PcInputReciever();

	// Initialize the main window
	MainWindow = new Window(L"2D ENGINE", hInstance, PcReciever);

	// Create a DirectX Asset Manager
	DirectXAssetManager* _dx = new DirectXAssetManager();

	// Assign it as the system's asset manager
	ResourceManager = _dx;

	// Pass it along to the scene factory...
	SceneManager = new SceneFactory(ResourceManager, GamepadReciever, PcReciever);

	// ...and to the renderer, which is also a DirectX renderer
	GameRenderer = new DirectXRenderer(_dx);

	VSettings = new VideoSettings();

	LastFrameTime = NULL;
	NumberOfFramesMeasured = 0;
}


Kernel::~Kernel()
{
	delete hInstance;
	delete MainWindow;
	delete GamepadReciever;
	delete PcReciever;
	delete ResourceManager;
	delete SceneManager;
	delete GameRenderer;
	delete Log;
	delete VSettings;
}


int Kernel::SetupDemoScene()
{
	SetActiveScene(SceneManager->CreateNewSceneFromFile("Data/Scenes/SAMPLE.scene"));
	GameRenderer->SetDefaultTextFormat("Arial", 50.0f, RED, 1.0f);
	return 1;
}


int CreateNewWindow(Window* _window)
{
	_window->Launch();
	return 1;
}


int Kernel::Run()
{
	// Load the video settings before doing anything video-related
	VSettings->ImportVideoSettings();

	// Pass the video settings to the window and the renderer
	MainWindow->SetVideoSettings(VSettings);
	GameRenderer->SetVideoSettings(VSettings);

	// Create a new window in a thread, so that the rest runs asynchronously
	std::thread t1(CreateNewWindow, MainWindow);

	while (!MainWindow->IsUp())
	{
		// Wait until the window is finished
	}

	// Initialize the renderer
	int _result = GameRenderer->Init(&MainWindow->Handle);

	SetupDemoScene();

	// Enter the game loop
	while (Running())
	{
		OnGameUpdate();
	}

	t1.join();

	return 1;
}


int Kernel::OnGameUpdate()
{
	// Read input if available
	if(GamepadReciever) GamepadReciever->ReadInput();
	if(PcReciever) PcReciever->ReadInput();

	// Call Act() on all entities in the active scene
	ActiveScene->OnGameUpdate();

	// Draw the next frame
	GameRenderer->Render(ActiveScene);

	// Calculate the framerate
	if (VSettings->TrackFramerate) CalculateCurrentFramerate();

	return 1;
}


int Kernel::LogNewSession()
{
	Log->Log("\n-------------------------------\n");
	Log->Log("NEW ENGINE SESSION STARTED HERE\n");
	Log->Log("-------------------------------\n");

	return 1;
}


bool Kernel::Running()
{
	return MainWindow->IsUp();
}


int Kernel::SetActiveScene(Scene* _scene)
{
	ActiveScene = _scene;
	Log->Log("\n\nSetting the active scene to: ");
	Log->Log(_scene->GetName());
	return 1;
}

int Kernel::CalculateCurrentFramerate()
{
	clock_t _currentTime = clock();

	if (LastFrameTime == NULL) LastFrameTime = _currentTime;

	float _frameElapsedTime = ((float)_currentTime - LastFrameTime) / CLOCKS_PER_SEC;
	LastFrameTime = _currentTime;

	FrametimeList[NumberOfFramesMeasured] = _frameElapsedTime;
	++NumberOfFramesMeasured;

	if (NumberOfFramesMeasured == FRAMES_MEASURED)
	{
		float _frametimeBatch = 0;

		for (int i = 0; i < FRAMES_MEASURED; ++i)
		{
			_frametimeBatch += FrametimeList[i];
			FrametimeList[i] = NULL;
		}

		float _avgFrametime = _frametimeBatch / FRAMES_MEASURED;
		float _framerate = 1 / _frameElapsedTime;
		GameRenderer->SetFPSToDraw(std::round(_framerate));
		NumberOfFramesMeasured = 0;
	}

	return 1;
}


int WindowThread(Window* _window)
{
	_window->Launch();
	return 1;
}