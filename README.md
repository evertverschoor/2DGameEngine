# 2DGameEngine

## Planned Work

-> Finalize and optimize Gravity

-> Look at collisions stuff

-> Unfocus postprocess effect

-> Support for day/night cycle

-> Depth of field postprocess effect

-> Fade in/out effect

-> Camera remote control

-> Convert to DLL

-> Allow for normal alt-tabbing without the mouse getting stuck on NORMAL camera move


## Could Haves

-> OpenGL Renderer for Mac and Linux support (also xinput and xaudio alternatives?)


## Changelog

### Sept. 10, 2015

-> Added Sharpening and Motion Blur postprocessing effects, and a class to test motion blur through moving the mouse.


### Sept. 11, 2015

-> Added Saturation effect and support for multiple postprocessing effects to work at the same time.

-> Bit of refactoring and renaming some classes to more proper names, stable build before majoring refactoring that might break stuff.

-> Fixed code convention for class variable names, added more documentation where needed and removed obsolete includes.


### Sept. 12, 2015

-> Added sound engine using XAudio2, can now load and unload sounds and play them.

-> Split VideoSettings and GraphicsSettings into two files, added Brighten effect, fixed Sharpen visual bug.


### Sept. 13, 2015

-> Added a camera with working mouse movement mode, hid the cursor

-> Fixed visual bug where rotated entities would display at a wrong location after moving the camera

-> Fixed visual bug where motion blur would keep going even after reaching the border of the scene


### Sept. 15, 2015

-> Removed SceneFactory and SceneLoader, and the scene and entity files

-> Allowed for entities and scenes to be created outside the engine project and to be played by the engine

-> Added a splash screen to show after the engine is ready to play and before it starts rendering a scene


### Sept. 16, 2015

-> Added ENTITY_CHASE camera mode, removed EDGE_PAN because it's probably not gonna be used

-> Added hitbox property on entities

-> Added background asset URI property to scenes, so you no longer need to use an entity as a background

-> Fixed a bug where sometimes the display driver would crash during load time

-> Added background PERSIST, MOVE and SLOW_MOVE options, making it behave differently as you move the camera

-> Deleted ControllableEntity

-> StartScene() now orders the entities in a scene by z-index, so lower z-index is overlapped by higher z-indexes


### Sept. 18, 2015

-> Added framerate independence in camera and entity movement (they move at a constant speed regardless of fps)

-> Added support for entities having more than one asset, loading them all during loadtime and switching between them during runtime
   
-> Added partial collision detection (if an entity wants to move into another one, it doesn't move next to it yet, instead it stays where it is, leaving a small gap)


### Sept. 19, 2015

-> Fixed major bug where entities would be attracted to 0,0 on any resolution other than 1080p and would start moving to 0,0 at 1080p anyway if you moved the camera,
   by reworking the resolution independence through the usage of memory dumps (this is far better anyway)
   

### Sept. 20, 2015

-> Finished proper collision detection that now suggests what position an entity should take to get as close to the target entity as possible

-> Added scene-wide gravity

-> Added collision handling for all entities (entity and collisiondetector #include each other, it works??? god help us all)


### Sept. 21, 2015

-> Fixed motion blur to a more proper way done by the renderer

-> Fixed gamepad camera movement happening more smoothly now


## Benchmarks

	Always 1080p, maxed out everything there is at the time.
	Running on weaker card without vsync(so the framerate isnt capped at 60)
	Specs: A10-5750M with Radeon HD 8650G, Windows 10

### Sept. 10, 2015

-> avg 50-60fps during heavy motion blur


### Sept. 11, 2015

-> avg 60+fps during heavy motion blur


### Sept. 21, 2015

-> avg 40fps during heavy motion blur, collisions and gravity

## How to use

	/**********************
	**	Main entry function
	***********************/

	// Initialize kernel
	Kernel* _kernel = new Kernel(&hInstance);

	// Initialize engine components
	_kernel->Init(L"Window Display Name Here");

	// Start running the engine in a separate thread
	std::thread _thread(runnerThread, _kernel);

	// Create a demo scene
	CreateDemoScene(_kernel);

	_thread.join();

	// The end
	return 1;
	
	
	
	/***************
	**	runnerThread
	****************/
	
	_kernel->Run();
	return 1;
	
	
	
	/******************
	**	CreateDemoScene
	*******************/
	
	while (!_kernel->Ready())
	{
		// Wait for the kernel to get ready
	}

	// Create scene Gotham
	Gotham* _gotham = new Gotham();

	// Create entity Batman
	Batman* _batman = new Batman();
	_batman->JumpTo(800, 300);
	_batman->SetZindex(2);
	_batman->SetDirection(0);

	// Get the pc input reciever from the kernel
	PcInputReciever* _pcInput = _kernel->GetPcInputReciever();
	GamepadInputReciever* _gamepadInput = _kernel->GetGamepadInputReciever();

	// Make Batman an input handler
	_pcInput->AddPcHandler(_batman);
	_gamepadInput->AddGamepadHandler(_batman);

	// Put Batman in Gotham
	_gotham->AddEntity(_batman);

	// Set camera movement to ENTITY_CHASE and pass Batman along
	_kernel->SetCameraMovement(ENTITY_CHASE, _batman);

	// Create second entity Batman so we can tell if we're entity chasing
	Batman* _batmanTwo = new Batman();
	_batmanTwo->JumpTo(100, 300);
	_batmanTwo->SetDirection(0);
	_batmanTwo->SetZindex(1);
	_gotham->AddEntity(_batmanTwo);

	// Load the assets that belong to the scene
	_kernel->GetAssetManager()->LoadScene(_gotham);

	// Pass the scene back to the kernel to start
	_kernel->StartScene(_gotham);

	// Load in some music
	AudioEngine::Instance()->GetAudioManager()->LoadAudioPiece("Audio/Music/arkham_knight.wav");

	// Play the music
	AudioEngine::Instance()->GetAudioPlayer()->PlayAudioPiece("Audio/Music/arkham_knight.wav");
	
	return 1;
	
	
	
	/************************
	** Gotham.cpp Constructor
	*************************/
	
	// Set name and size
	SetName("Gotham");
	SetSize(new Dimension(4000, 2000));

	// Set background image and type
	SetBackgroundAssetURI("Assets/Backgrounds/gotham_back.jpg");
	SetBackgroundType(SLOW_MOVE);
	
	
	
	/************************
	** Batman.cpp Constructor
	*************************/
	
	// Set the asset URI and appropriate hitbox for this entity
	SetAssetURI("Assets/UI/ArkhamKnight.jpg");
	SetHitbox(960, 600);

	// Set speed and phase property
	SetSpeed(10);
	SetPhaseState(false);