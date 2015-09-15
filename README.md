# 2DGameEngine

## Planned Work

-> Optimization

-> Allow for normal alt-tabbing without the mouse getting stuck

-> Entity chase camera move mode

-> Gravity

-> Collision detection

-> Support for more than one asset per entity (animations?)

-> Implement proper way of making entities move (not a certain distance every frame)

-> Convert to DLL

-> Support for actually being able to use this as a library


## Could Haves

-> OpenGL Renderer for Mac and Linux support (also xinput alternative?)


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


## Benchmarks

	Always 1080p, maxed out everything there is at the time.
	Running on weaker card without vsync(so the framerate isnt capped at 60)
	Specs: A10-5750M with Radeon HD 8650G, Windows 10

### Sept. 10, 2015

-> avg 50-60fps during heavy motion blur


### Sept. 11, 2015

-> avg 60+fps during heavy motion blur

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
	_batman->SetDirection(0);

	// Get the pc input reciever from the kernel
	PcInputReciever* _pcInput = _kernel->GetPcInputReciever();

	// Make Batman an input handler
	_pcInput->AddPcHandler(_batman);

	// Put Batman in Gotham
	_gotham->AddEntity(_batman);

	// Load the assets that belong to the scene
	_kernel->GetAssetManager()->LoadScene(_gotham);

	// Pass the scene back to the kernel to start
	_kernel->StartScene(_gotham);

	// Load in some music
	AudioEngine::Instance()->GetAudioManager()->LoadAudioPiece("Audio/Music/arkham_knight.wav");

	// Play the music
	AudioEngine::Instance()->GetAudioPlayer()->PlayAudioPiece("Audio/Music/arkham_knight.wav");

	return 1;