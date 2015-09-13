#ifndef XAUDIO2MANAGER_H
#define XAUDIO2MANAGER_H

#include "AudioManager.h"
#include <xaudio2.h>
#include <fstream>
#include <map>

class XAudio2Manager : public AudioManager
{
public:
	XAudio2Manager();
	~XAudio2Manager();

	int LoadAudioPiece(std::string);

	int UnloadAudioPiece(std::string);

	WAVEFORMATEX* GetFormat(std::string);

	XAUDIO2_BUFFER* GetBuffer(std::string);
private:
	std::map<std::string, WAVEFORMATEX> waveFormatMap;
	std::map<std::string, XAUDIO2_BUFFER> audioBufferMap;
	std::map<std::string, BYTE*> waveDataMap;
};

#endif