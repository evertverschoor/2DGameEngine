#include "XAudio2Manager.h"


XAudio2Manager::XAudio2Manager()
{
}


XAudio2Manager::~XAudio2Manager()
{
}


int XAudio2Manager::LoadAudioPiece(std::string _file)
{
	// Create a filestream for the given file
	std::ifstream _inFile(_file, std::ios::binary | std::ios::in);

	// Return 0 if it's a bad file
	if (_inFile.bad())
		return 0;

	DWORD dwChunkId = 0, dwFileSize = 0, dwChunkSize = 0, dwExtra = 0;

	//look for 'RIFF' chunk identifier
	_inFile.seekg(0, std::ios::beg);
	_inFile.read(reinterpret_cast<char*>(&dwChunkId), sizeof(dwChunkId));
	if (dwChunkId != 'FFIR')
	{
		_inFile.close();
		return false;
	}

	_inFile.seekg(4, std::ios::beg); //get file size
	_inFile.read(reinterpret_cast<char*>(&dwFileSize), sizeof(dwFileSize));
	if (dwFileSize <= 16)
	{
		_inFile.close();
		return false;
	}

	_inFile.seekg(8, std::ios::beg); //get file format
	_inFile.read(reinterpret_cast<char*>(&dwExtra), sizeof(dwExtra));
	if (dwExtra != 'EVAW')
	{
		_inFile.close();
		return false;
	}

	//look for 'fmt ' chunk id
	bool bFilledFormat = false;
	for (unsigned int i = 12; i < dwFileSize;)
	{
		_inFile.seekg(i, std::ios::beg);
		_inFile.read(reinterpret_cast<char*>(&dwChunkId), sizeof(dwChunkId));
		_inFile.seekg(i + 4, std::ios::beg);
		_inFile.read(reinterpret_cast<char*>(&dwChunkSize), sizeof(dwChunkSize));
		if (dwChunkId == ' tmf')
		{
			_inFile.seekg(i + 8, std::ios::beg);
			_inFile.read(reinterpret_cast<char*>(&waveFormatMap[_file]), sizeof(waveFormatMap[_file]));
			bFilledFormat = true;
			break;
		}
		dwChunkSize += 8; //add offsets of the chunk id, and chunk size data entries
		dwChunkSize += 1;
		dwChunkSize &= 0xfffffffe; //guarantees WORD padding alignment
		i += dwChunkSize;
	}
	if (!bFilledFormat)
	{
		_inFile.close();
		return false;
	}

	//look for 'data' chunk id
	bool bFilledData = false;
	for (unsigned int i = 12; i < dwFileSize;)
	{
		_inFile.seekg(i, std::ios::beg);
		_inFile.read(reinterpret_cast<char*>(&dwChunkId), sizeof(dwChunkId));
		_inFile.seekg(i + 4, std::ios::beg);
		_inFile.read(reinterpret_cast<char*>(&dwChunkSize), sizeof(dwChunkSize));
		if (dwChunkId == 'atad')
		{
			waveDataMap[_file] = new BYTE[dwChunkSize];
			_inFile.seekg(i + 8, std::ios::beg);
			_inFile.read(reinterpret_cast<char*>(waveDataMap[_file]), dwChunkSize);
			audioBufferMap[_file].AudioBytes = dwChunkSize;
			audioBufferMap[_file].pAudioData = waveDataMap[_file];
			audioBufferMap[_file].PlayBegin = 0;
			audioBufferMap[_file].PlayLength = 0;
			bFilledData = true;
			break;
		}
		dwChunkSize += 8; //add offsets of the chunk id, and chunk size data entries
		dwChunkSize += 1;
		dwChunkSize &= 0xfffffffe; //guarantees WORD padding alignment
		i += dwChunkSize;
	}
	if (!bFilledData)
	{
		_inFile.close();
		return 0;
	}

	_inFile.close();
	return 1;
}


int XAudio2Manager::UnloadAudioPiece(std::string _file)
{
	waveFormatMap.erase(_file);
	audioBufferMap.erase(_file);
	waveDataMap.erase(_file);

	return 1;
}


WAVEFORMATEX* XAudio2Manager::GetFormat(std::string _file)
{
	return &waveFormatMap[_file];
}


XAUDIO2_BUFFER* XAudio2Manager::GetBuffer(std::string _file)
{
	return &audioBufferMap[_file];
}