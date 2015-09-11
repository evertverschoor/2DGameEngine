#include "VideoSettings.h"


VideoSettings::VideoSettings()
{
}


VideoSettings::~VideoSettings()
{
	delete screenRes;
	delete monitorRes;
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
	std::string delimiter = ";";

	int i = 0;
	size_t pos = 0;
	std::string token;
	while ((pos = _string.find(delimiter)) != std::string::npos) {
		token = _string.substr(0, pos);
		_strings[i] = token;
		++i;
		_string.erase(0, pos + delimiter.length());
	}

	int _width, _height;

	// Iterate through each line read
	for (int i = 0; i < _strings->length(); i++)
	{
		// Check the fullscreen setting
		if (_strings[i].find("Fullscreen") != std::string::npos)
		{
			std::string _fullscreenString = _strings[i].substr(11, _strings[i].find(";") - 11);
			fullscreen = (_fullscreenString == "1") ? true : false;
		}

		// Check the vsync setting
		else if (_strings[i].find("Vsync") != std::string::npos)
		{
			std::string _vsyncString = _strings[i].substr(6, _strings[i].find(";") - 6);
			vsync = (_vsyncString == "1") ? true : false;
		}

		// Check the track fps setting
		else if (_strings[i].find("TrackFPS") != std::string::npos)
		{
			std::string _framerateString = _strings[i].substr(9, _strings[i].find(";") - 9);
			trackFramerate = (_framerateString == "1") ? true : false;
		}

		// Check the motion blur setting
		else if (_strings[i].find("Motion") != std::string::npos)
		{
			std::string _blurString = _strings[i].substr(11, _strings[i].find(";") - 11);
			motionBlur = (_blurString == "1") ? true : false;
		}

		// Check the sharpen setting
		else if (_strings[i].find("Sharpen") != std::string::npos)
		{
			std::string _sharpString = _strings[i].substr(8, _strings[i].find(";") - 8);
			sharpen = (_sharpString == "1") ? true : false;
		}

		// Check the saturation setting
		else if (_strings[i].find("Saturation") != std::string::npos)
		{
			std::string _saturateString = _strings[i].substr(11, _strings[i].find(";") - 11);
			saturation = (_saturateString == "1") ? true : false;
		}

		// Check the width setting
		else if (_strings[i].find("DrawWidth") != std::string::npos)
		{
			std::string _widthString = _strings[i].substr(10, _strings[i].find(";") - 10);
			_width = atoi(_widthString.c_str());
		}

		// Check the height setting
		else if (_strings[i].find("DrawHeight") != std::string::npos)
		{
			std::string _heightString = _strings[i].substr(11, _strings[i].find(";") - 11);
			_height = atoi(_heightString.c_str());
		}

		else
		{
			break;
		}
	}

	// Put it in a screen resolution object
	screenRes = new Dimension(_width, _height);

	// Log the results
	Logger::Instance()->Log("\n\nImported these Video Settings:");
	Logger::Instance()->Log("\nFull Screen: ");
	Logger::Instance()->Log(fullscreen);
	Logger::Instance()->Log("\nVsync: ");
	Logger::Instance()->Log(vsync);
	Logger::Instance()->Log("\nTrack FPS: ");
	Logger::Instance()->Log(trackFramerate);
	Logger::Instance()->Log("\nMotion Blur: ");
	Logger::Instance()->Log(motionBlur);
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

	monitorRes = new Dimension(desktop.right, desktop.bottom);

	Logger::Instance()->Log("\n\nDetected Monitor Resolution: ");
	Logger::Instance()->Log(monitorRes->width);
	Logger::Instance()->Log("x");
	Logger::Instance()->Log(monitorRes->height);

	return 1;
}