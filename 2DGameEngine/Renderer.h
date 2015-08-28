#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Windows.h"
#include "VideoSettings.h"
#include "Dimension.h"
#include "Color.h"

/// <summary>
/// The renderer is an interface that will be realized by a DirectX Renderer.
/// </summary>
class Renderer
{
public:
	virtual ~Renderer() { }

	/// <summary>
	/// Render all entities in a scene.
	/// </summary>
	virtual int Render(Scene*) = 0;

	/// <summary>
	/// Write some text somewhere on the screen.
	/// </summary>
	virtual int WriteText(std::string, Position*) = 0;

	/// <summary>
	/// Set a custom text format.
	/// @param1 The name of the font family;
	/// @param2 The size of the font.
	/// @param3 The font color.
	/// @param4 The font transparency.
	/// </summary>
	virtual int SetDefaultTextFormat(std::string, float, Color, float) = 0;

	/// <summary>
	/// Initialize the renderer with a window handle.
	/// </summary>
	virtual int Init(HWND*) = 0;

	/// <summary>
	/// Set the video settings for the render quality.
	/// </summary>
	virtual int SetVideoSettings(VideoSettings*) = 0;

	/// <summary>
	/// Set the virtual resolution (recommended is the target size of the assets)
	/// </summary>
	virtual int SetVirtualResolution(Dimension*) = 0;

	/// <summary>
	/// If the Track FPS option is turned on the kernel will pass the framerate here.
	/// </summary>
	virtual int SetFPSToDraw(int) = 0;
};

#endif