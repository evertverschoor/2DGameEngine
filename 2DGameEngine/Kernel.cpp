#include "Kernel.h"


Kernel::Kernel(HINSTANCE* _hInstance)
{
	// Set the hInstance
	hInstance = _hInstance;

	// Set the virtual resolution to default values
	virtualResolution.width = DEFAULT_VIRTUAL_RESOLUTION_WIDTH;
	virtualResolution.height = DEFAULT_VIRTUAL_RESOLUTION_HEIGHT;
}


Kernel::Kernel(HINSTANCE* _hInstance, int _virtualResolutionWidth, int _virtualResolutionHeight)
{
	// Set the hInstance
	hInstance = _hInstance;

	// Set the virtual resolution
	virtualResolution.width = _virtualResolutionWidth;
	virtualResolution.height = _virtualResolutionHeight;
}


Kernel::~Kernel()
{
	delete hInstance;
	delete mainWindow;
	delete gamepadReciever;
	delete pcReciever;
	delete resourceManager;
	delete gameRenderer;
	delete log;
	delete vSettings;
}


int CreateNewWindow(Window* _window)
{
	_window->Launch();
	return 1;
}


int Kernel::Init(LPCWSTR _name)
{
	// Get a copy of the logger and mark a new session in the log file
	log = Logger::Instance();
	LogNewSession();

	// Create the XAudio2 Manager
	XAudio2Manager* _xa = new XAudio2Manager();

	// Initialize the audio manager as it
	audioManager = _xa;

	// Initialize the Audio player as XAudio2 and pass the XAudio2 manager along
	audioPlayer = new XAudio2Player(_xa);

	// Initialize the Audio Engine with the Audio Player
	audioEngine = new AudioEngine(audioPlayer, audioManager);

	// Create the Gamepad Input Reciever as Xinput, if there are gamepads connected
	gamepadReciever = new XInputReciever();
	if (!gamepadReciever->HasGamepadsConnected()) gamepadReciever = NULL;

	// Create the Pc Input Reciever
	pcReciever = new PcInputReciever();

	// Initialize the main window with the appropriate name
	mainWindow = new Window(_name, hInstance, pcReciever);

	// Create a DirectX Asset Manager
	DirectXAssetManager* _dx = new DirectXAssetManager();

	// Assign it as the system's asset manager
	resourceManager = _dx;

	// ...and to the renderer, which is also a DirectX renderer
	gameRenderer = new DirectXRenderer(_dx);

	// Initialize the video settings
	vSettings = new VideoSettings();

	// Import the video and graphics settings
	vSettings->ImportVideoSettings();
	vSettings->ImportGraphicsSettings();

	// Initialize the GFX Controller and pass it to the renderer (and camera later)
	gfx = new GFXController();
	gameRenderer->SetGFXController(gfx);

	// Get a copy of the timecontroller
	time = TimeController::Instance();

	// Initialize the camera and pass timecontroller along
	camera = new Camera(0, &virtualResolution, gfx, vSettings, time);

	// Make pc reciever
	pcReciever->AddPcHandler(camera);

	// Make gamepad reciever too if there are gamepads
	if (!gamepadReciever == NULL) gamepadReciever->AddGamepadHandler(camera);

	// Pass the camera to the renderer
	gameRenderer->SetCamera(camera);

	// Pass the virtual resolution to the camera and renderer
	gameRenderer->SetVirtualResolution(&virtualResolution);

	// Last frame time is never, but we say now since it will only mess up the first frame and we don't care
	lastFrameTime = clock();

	// 0 frames measured as of now
	numberOfFramesMeasured = 0;

	// Pass the video settings to the window and the renderer
	mainWindow->SetVideoSettings(vSettings);
	gameRenderer->SetVideoSettings(vSettings);

	// No active scene yet
	activeScene = NULL;

	// Not ready to be used yet
	ready = FALSE;

	return 1;
}


int Kernel::SetCameraMovement(CameraMovement _value)
{
	camera->SetCameraMovement(_value);
	return 1;
}


int Kernel::SetCameraMovement(CameraMovement _value, Entity* _entity)
{
	SetCameraMovement(_value);
	camera->SetChasableEntity(_entity);

	return 1;
}


AssetManager* Kernel::GetAssetManager()
{
	return resourceManager;
}


PcInputReciever* Kernel::GetPcInputReciever()
{
	return pcReciever;
}


GamepadInputReciever* Kernel::GetGamepadInputReciever()
{
	if (!gamepadReciever) return NULL;
	return gamepadReciever;
}


int Kernel::StartScene(Scene* _scene)
{
	_scene->OrderByZIndex();
	camera->SetActiveSceneSize(_scene->GetSize());
	activeScene = _scene;

	log->Log("\n\nStarting Scene: ");
	log->Log(_scene->GetName());

	return 1;
}


bool Kernel::Ready()
{
	return ready;
}


int Kernel::Run()
{
	std::thread _windowThread(CreateNewWindow, mainWindow);

	while (!mainWindow->IsUp())
	{
		// Wait until the window is finished
	}

	// Initialize the renderer
	gameRenderer->Init(&mainWindow->handle);

	// Load in the splash screen image for showing when the engine is ready
	resourceManager->LoadSingleBitmap("Assets/Engine/splash_screen.png");

	// Show the splash screen
	ShowEngineSplash();

	// Signal that the engine is ready to be used
	ready = TRUE;

	// Enter the game loop
	while (Running())
	{
		if (activeScene) OnGameUpdate();
	}

	// End the window thread (killing the window)
	_windowThread.join();

	return 1;
}


int Kernel::OnGameUpdate()
{
	// Update the time
	time->Update();

	// Read input if available
	if(gamepadReciever) gamepadReciever->ReadInput();
	if(pcReciever) pcReciever->ReadInput();

	// Call Act() on all entities in the active scene and on the camera
	activeScene->OnGameUpdate();

	// Draw the next frame
	gameRenderer->Render(activeScene);

	// Calculate the framerate
	if (vSettings->trackFramerate) CalculateCurrentFramerate();

	return 1;
}


int Kernel::LogNewSession()
{
	log->Log("\n-------------------------------\n");
	log->Log("NEW ENGINE SESSION STARTED HERE\n");
	log->Log("-------------------------------\n");

	return 1;
}


bool Kernel::Running()
{
	return mainWindow->IsUp();
}

int Kernel::CalculateCurrentFramerate()
{
	clock_t _currentTime = clock();

	float _frameElapsedTime = ((float)_currentTime - lastFrameTime) / CLOCKS_PER_SEC;
	lastFrameTime = _currentTime;

	frametimeList[numberOfFramesMeasured] = _frameElapsedTime;
	++numberOfFramesMeasured;

	if (numberOfFramesMeasured == FRAMES_MEASURED)
	{
		float _frametimeBatch = 0;

		for (int i = 0; i < FRAMES_MEASURED; ++i)
		{
			_frametimeBatch += frametimeList[i];
			frametimeList[i] = NULL;
		}

		float _avgFrametime = _frametimeBatch / FRAMES_MEASURED;
		float _framerate = 1 / _frameElapsedTime;
		gameRenderer->SetFPSToDraw(_framerate);
		numberOfFramesMeasured = 0;
	}

	return 1;
}


int Kernel::ShowEngineSplash()
{
	gameRenderer->DrawEngineSplash(0, 0, 0);
	return 1;
}