#ifndef VIDEOSETTINGS_H
#define VIDEOSETTINGS_H

#include "Dimension.h"
#include "Logger.h"
#include "FileReader.h"

/// <summary>
/// A simple model that contains the video settings for the window and renderer from VideoSettings.ini
/// ScreenRes is the render resolution, while MonitorRes is the monitor's native resolution
/// It also contains additional graphics settings from GraphicsSettings.ini
/// </summary>
class VideoSettings
{
public:
	VideoSettings();
	~VideoSettings();

	/// <summary>
	/// True for fullscreen, false for windowed.
	/// </summary>
	bool fullscreen;

	/// <summary>
	/// True to cap the framerate to the monitor's refresh rate, false to always draw frames to the monitor whenever possible.
	/// </summary>
	bool vsync;

	/// <summary>
	/// Display the framerate at the upper left corner
	/// </summary>
	bool trackFramerate;

	/// <summary>
	/// Blur the screen when rapid movement takes place, effect diminishes at higher framerates.
	/// </summary>
	bool motionBlur;

	/// <summary>
	/// Sharpen the output image.
	/// </summary>
	bool sharpen;

	/// <summary>
	/// Increase the saturation of the image.
	/// </summary>
	bool saturate;

	/// <summary>
	/// Increase the image shadows and highlights.
	/// </summary>
	bool brighten;

	/// <summary>
	/// Resolution the image will be drawn at, regardless of the actual window/screen size.
	/// </summary>
	Dimension* screenRes;

	/// <summary>
	/// Size of the host pc's monitor.
	/// </summary>
	Dimension* monitorRes;

	/// <summary>
	/// Load the video settings from VideoSettings.ini
	/// </summary>
	int ImportVideoSettings();

	/// <summary>
	/// Load the video settings from GraphicsSettings.ini
	/// </summary>
	int ImportGraphicsSettings();
private:
	int SetVideoSettingsFromString(std::string);
	int SetGraphicsSettingsFromString(std::string);
	int DetectMonitorResolution();
};

#endif