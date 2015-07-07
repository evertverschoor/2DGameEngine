#ifndef SCREENRESOLUTION_H
#define SCREENRESOLUTION_H

/// <summary>
/// A screen resolution is a simple model that contains a screen width and height.
/// </summary>
class ScreenResolution
{
public:
	ScreenResolution(int, int);
	~ScreenResolution();
	int Width;
	int Height;
};

#endif