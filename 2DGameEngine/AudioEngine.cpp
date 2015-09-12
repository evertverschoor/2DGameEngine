#include "AudioEngine.h"


AudioEngine* AudioEngine::a_instance = NULL;
AudioPlayer* AudioEngine::audioPlayer = NULL;
AudioManager* AudioEngine::audioManager = NULL;


AudioEngine::AudioEngine(AudioPlayer* _audioPlayer, AudioManager* _audioManager)
{
	audioPlayer = _audioPlayer;
	audioManager = _audioManager;
}


AudioEngine::~AudioEngine()
{
	delete a_instance;
}


AudioPlayer* AudioEngine::GetAudioPlayer()
{
	return audioPlayer;
}

AudioManager* AudioEngine::GetAudioManager()
{
	return audioManager;
}


AudioEngine* AudioEngine::Instance()
{
	if (!a_instance) a_instance = new AudioEngine(audioPlayer, audioManager);

	if (!audioPlayer)
	{
		Logger::Instance()->Log("Something tried to get an instance of AudioEngine but the AudioPlayer hasn't been passed along yet.");
	}

	if (!audioPlayer)
	{
		Logger::Instance()->Log("Something tried to get an instance of AudioEngine but the AudioManager hasn't been passed along yet.");
	}

	return a_instance;
}