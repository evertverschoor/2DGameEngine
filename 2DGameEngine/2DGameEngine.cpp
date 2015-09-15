#include "Kernel.h"
#include "Gotham.h"
#include "Batman.h"
#include "AudioEngine.h"

int runnerThread(Kernel* _kernel)
{
	_kernel->Run();
	return 1;
}

int CreateDemoScene(Kernel* _kernel)
{
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
	//AudioEngine::Instance()->GetAudioPlayer()->PlayAudioPiece("Audio/Music/arkham_knight.wav");

	return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdline, int iCmdShow)
{
	// Initialize kernel
	Kernel* _kernel = new Kernel(&hInstance);

	// Initialize engine components
	_kernel->Init(L"Coole batman game joh");

	// Start running the engine in a separate thread
	std::thread _thread(runnerThread, _kernel);

	// Create a demo scene
	CreateDemoScene(_kernel);

	_thread.join();

	return 1;
}