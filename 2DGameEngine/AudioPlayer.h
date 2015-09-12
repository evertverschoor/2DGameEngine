#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <string>

/// <summary>
/// The Audio Player can play and control audio pieces that have been loaded by the Audio Manager.
/// </summary>
class AudioPlayer
{
public:
	virtual ~AudioPlayer() { };

	/// <summary>
	/// Play an audio piece that has been loaded by the Audio Manager.
	/// @param The path to the audio file that corresponds to the audio piece.
	/// </summary>
	virtual int PlayAudioPiece(std::string) = 0;

	/// <summary>
	/// Toggle a playing audio piece between paused and playing.
	/// @param The path to the audio file that corresponds to the audio piece.
	/// </summary>
	virtual int ToggleAudioPiece(std::string) = 0;

	/// <summary>
	/// Stop playing an audio piece entirely.
	/// @param The path to the audio file that corresponds to the audio piece.
	/// </summary>
	virtual int StopAudioPiece(std::string) = 0;
};

#endif