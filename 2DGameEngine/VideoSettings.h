#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H

#include "ScreenResolution.h"
#include <string>

/// <summary>
/// A simple model that contains the video settings for the window and renderer.
/// ScreenRes is the render resolution, while MonitorRes is the monitor's native resolution.
/// </summary>
class VideoSettings
{
public:
	VideoSettings();
	~VideoSettings();

	bool Fullscreen;
	ScreenResolution* ScreenRes;
	ScreenResolution* MonitorRes;

	/// <summary>
	/// Load the video settings from the video settings file.
	/// </summary>
	int ImportVideoSettings();
private:
	int SetVideoSettingsFromString(std::string);
	int DetectMonitorResolution();
};

#endif