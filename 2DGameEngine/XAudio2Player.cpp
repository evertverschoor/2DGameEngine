#include "XAudio2Player.h"


XAudio2Player::XAudio2Player(XAudio2Manager* _audioManager)
{
	audioManager = _audioManager;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	//create the engine
	if (FAILED(XAudio2Create(&audioEngine)))
	{
		CoUninitialize();
		Logger::Instance()->Log("\nFailed to create XAudio2 Engine");
	}

	//create the mastering voice
	if (FAILED(audioEngine->CreateMasteringVoice(&masterVoice)))
	{
		audioEngine->Release();
		CoUninitialize();
		Logger::Instance()->Log("\nFailed to create XAudio2 Mastering Voice");
	}
}


XAudio2Player::~XAudio2Player()
{
	audioEngine->Release();
	CoUninitialize();
}


int XAudio2Player::PlayAudioPiece(std::string _file)
{
	// Create the source voice for this audio piece, based on loaded wave format
	if (FAILED(audioEngine->CreateSourceVoice(&sourceVoiceMap[_file], audioManager->GetFormat(_file))))
	{
		Logger::Instance()->Log("\nFailed to create XAudio2 Source Voice for: ");
		Logger::Instance()->Log(_file);
		return 0;
	}

	sourceVoiceMap[_file]->Start();
	sourceVoiceMap[_file]->SubmitSourceBuffer(audioManager->GetBuffer(_file));

	return 1;
}

int XAudio2Player::ToggleAudioPiece(std::string _file)
{
	// TODO implement
	return 1;
}

int XAudio2Player::StopAudioPiece(std::string _file)
{
	// TODO implement
	return 1;
}