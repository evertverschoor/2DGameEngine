#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include "AudioPlayer.h"
#include "AudioManager.h"
#include "Logger.h"

/// <summary>
/// The Audio Engine is accessible globally and can provide the Audio Player.
/// </summary>
class AudioEngine
{
public:
	AudioEngine(AudioPlayer*, AudioManager*);
	~AudioEngine();

	/// <summary>
	/// Get the one and only Audio Player.
	/// </summary>
	AudioPlayer* GetAudioPlayer();

	/// <summary>
	/// Get the one and only Audio Manager.
	/// </summary>
	AudioManager* GetAudioManager();

	/// <summary>
	/// Get the instance of the Audio Engine using a static call.
	/// </summary>
	static AudioEngine* Instance();
private:
	static AudioPlayer* audioPlayer;
	static AudioManager* audioManager;
	static AudioEngine* a_instance;
};

#endif