#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <string>

/// <summary>
/// The Audio Manager loads and unloads audio files for playback by the Audio Player.
/// </summary>
class AudioManager
{
public:
	virtual ~AudioManager() { };
	
	/// <summary>
	/// Load an audio piece from a file.
	/// @param The path to the audio file.
	/// </summary>
	virtual int LoadAudioPiece(std::string) = 0;

	/// <summary>
	/// Unload an audio piece.
	/// @param The path of the audio file that was used to load it.
	/// </summary>
	virtual int UnloadAudioPiece(std::string) = 0;
};

#endif