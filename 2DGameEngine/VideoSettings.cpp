#include "VideoSettings.h"
#include "Logger.h"
#include "FileReader.h"
#include "Logger.h"
#include "wtypes.h"
#include <iostream>



VideoSettings::VideoSettings()
{
}


VideoSettings::~VideoSettings()
{
	delete ScreenRes;
	delete MonitorRes;
}


int VideoSettings::ImportVideoSettings()
{
	std::string _videoSettings = FileReader::Instance()->ReadFile("Data/VideoSettings.ini");
	SetVideoSettingsFromString(_videoSettings);
	DetectMonitorResolution();
	return 1;
}


int VideoSettings::SetVideoSettingsFromString(std::string _string)
{
	std::string _strings[80];
	std::string delimiter = "=";

	int i = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = _string.find(delimiter)) != std::string::npos) {
		token = _string.substr(0, pos);
		_strings[i] = token;
		++i;
		_string.erase(0, pos + delimiter.length());
	}

	// Set the full screen option
	Fullscreen = (_strings[1] == "1") ? true : false;

	// Set the width
	int _width = atoi(_strings[3].c_str());

	// Set the height
	int _height = atoi(_strings[5].c_str());

	// Put it in a screen resolution object
	ScreenRes = new ScreenResolution(_width, _height);

	// Log the results
	Logger::Instance()->Log("\n\nImported these Video Settings:");
	Logger::Instance()->Log("\nFull Screen: ");
	Logger::Instance()->Log(Fullscreen);
	Logger::Instance()->Log("\nRender Resolution: ");
	Logger::Instance()->Log(_width);
	Logger::Instance()->Log("x");
	Logger::Instance()->Log(_height);

	return 1;
}


int VideoSettings::DetectMonitorResolution()
{
	RECT desktop;
	const HWND hDesktop = GetDesktopWindow();
	GetWindowRect(hDesktop, &desktop);

	MonitorRes = new ScreenResolution(desktop.right, desktop.bottom);

	Logger::Instance()->Log("\n\nDetected Monitor Resolution: ");
	Logger::Instance()->Log(MonitorRes->Width);
	Logger::Instance()->Log("x");
	Logger::Instance()->Log(MonitorRes->Height);

	return 1;
}