#include "Kernel.h"


Kernel::Kernel(HINSTANCE* _hInstance)
{
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

	vSettings = new VideoSettings();

	// Initialize the GFX Controller, passing the renderer along
	gfx = new GFXController(gameRenderer);

	lastFrameTime = NULL;
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
	SetActiveScene(sceneManager->CreateNewSceneFromFile("Data/Scenes/KNIGHT.scene"));
	gameRenderer->SetDefaultTextFormat("Arial", 50.0f, RED, 1.0f);

	MotionBlurTestClass* _test = new MotionBlurTestClass(gfx);
	pcReciever->AddPcHandler(_test);

	AudioEngine::Instance()->GetAudioManager()->LoadAudioPiece("Audio/Music/arkham_knight.wav");
	AudioEngine::Instance()->GetAudioPlayer()->PlayAudioPiece("Audio/Music/arkham_knight.wav");

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
	vSettings->ImportVideoSettings();

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
	log->Log("\n\nSetting the active scene to: ");
	log->Log(_scene->GetName());
	return 1;
}

int Kernel::CalculateCurrentFramerate()
{
	clock_t _currentTime = clock();

	if (lastFrameTime == NULL) lastFrameTime = _currentTime;

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
		gameRenderer->SetFPSToDraw(std::round(_framerate));
		numberOfFramesMeasured = 0;
	}

	return 1;
}


int WindowThread(Window* _window)
{
	_window->Launch();
	return 1;
}