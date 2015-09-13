#include "Kernel.h"


Kernel::Kernel(HINSTANCE* _hInstance)
{
	// Get a copy of the logger and mark a new session in the log file
	log = Logger::Instance();
	LogNewSession();

	// Set the hInstance
	hInstance = _hInstance;

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

	// Initialize the main window
	mainWindow = new Window(L"2D ENGINE", hInstance, pcReciever);

	// Create a DirectX Asset Manager
	DirectXAssetManager* _dx = new DirectXAssetManager();

	// Assign it as the system's asset manager
	resourceManager = _dx;

	// Pass it along to the scene factory...
	sceneManager = new SceneFactory(resourceManager, gamepadReciever, pcReciever);

	// ...and to the renderer, which is also a DirectX renderer
	gameRenderer = new DirectXRenderer(_dx);

	// Initialize the video settings
	vSettings = new VideoSettings();

	// Import the video and graphics settings
	vSettings->ImportVideoSettings();
	vSettings->ImportGraphicsSettings();

	// Set the virtual resolution
	virtualResolution.width = VIRTUAL_RESOLUTION_WIDTH;
	virtualResolution.height = VIRTUAL_RESOLUTION_HEIGHT;

	// Initialize the GFX Controller and pass it to the renderer (and camera later)
	gfx = new GFXController();
	gameRenderer->SetGFXController(gfx);

	// Initialize the camera
	camera = new Camera(0, &virtualResolution, gfx, vSettings);

	// Make pc reciever
	pcReciever->AddPcHandler(camera);

	// Make gamepad reciever too if ther are gamepads
	if(!gamepadReciever == NULL) gamepadReciever->AddGamepadHandler(camera);

	// Pass the camera to the renderer
	gameRenderer->SetCamera(camera);
	
	// Pass the virtual resolution to the camera and renderer
	gameRenderer->SetVirtualResolution(&virtualResolution);

	// Last frame time is never, but we say now since it will only mess up the first frame and we don't care
	lastFrameTime = clock();

	// 0 frames measured as of now
	numberOfFramesMeasured = 0;
}


Kernel::~Kernel()
{
	delete hInstance;
	delete mainWindow;
	delete gamepadReciever;
	delete pcReciever;
	delete resourceManager;
	delete sceneManager;
	delete gameRenderer;
	delete log;
	delete vSettings;
}


int Kernel::SetupDemoScene()
{
	SetActiveScene(sceneManager->CreateNewSceneFromFile("Data/Scenes/SAMPLE.scene"));
	gameRenderer->SetDefaultTextFormat("Arial", 50.0f, RED, 1.0f);

	return 1;
}


int CreateNewWindow(Window* _window)
{
	_window->Launch();
	return 1;
}


int Kernel::Run()
{
	// Pass the video settings to the window and the renderer
	mainWindow->SetVideoSettings(vSettings);
	gameRenderer->SetVideoSettings(vSettings);

	// Create a new window in a thread, so that the rest runs asynchronously
	std::thread t1(CreateNewWindow, mainWindow);

	while (!mainWindow->IsUp())
	{
		// Wait until the window is finished
	}

	// Initialize the renderer
	int _result = gameRenderer->Init(&mainWindow->handle);

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
	if(gamepadReciever) gamepadReciever->ReadInput();
	if(pcReciever) pcReciever->ReadInput();

	// Call Act() on all entities in the active scene
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


int Kernel::SetActiveScene(Scene* _scene)
{
	activeScene = _scene;
	camera->SetActiveSceneSize(_scene->GetSize());

	log->Log("\n\nSetting the active scene to: ");
	log->Log(_scene->GetName());

	return 1;
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
		//gameRenderer->SetFPSToDraw(std::round(_framerate));
		gameRenderer->SetFPSToDraw(_framerate);
		numberOfFramesMeasured = 0;
	}

	return 1;
}


int WindowThread(Window* _window)
{
	_window->Launch();
	return 1;
}