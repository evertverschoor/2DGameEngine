#ifndef XAUDIO2PLAYER_H
#define XAUDIO2PLAYER_H

#include "AudioPlayer.h"
#include "XAudio2Manager.h"
#include "Logger.h"
#include <xaudio2.h>
#include <map>

/// <summary>
/// XAudio2 implementation of the Audio Player.
/// </summary>
class XAudio2Player : public AudioPlayer
{
public:
	XAudio2Player(XAudio2Manager*);
	~XAudio2Player();

	int PlayAudioPiece(std::string);
	
	int ToggleAudioPiece(std::string);

	int StopAudioPiece(std::string);
private:
	IXAudio2* audioEngine;
	std::map<std::string, IXAudio2SourceVoice*> sourceVoiceMap;
	IXAudio2MasteringVoice* masterVoice;

	XAudio2Manager* audioManager;
};

#endif