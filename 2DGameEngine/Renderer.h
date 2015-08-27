#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Windows.h"
#include "VideoSettings.h"

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
	/// @param1 The name of the font.
	/// @param2 The size of the font.
	/// </summary>
	virtual int SetDefaultTextFormat(std::string, float) = 0;

	/// <summary>
	/// Initialize the renderer with a window handle.
	/// </summary>
	virtual int Init(HWND*) = 0;

	/// <summary>
	/// Set the video settings for the render quality.
	/// </summary>
	virtual int SetVideoSettings(VideoSettings*) = 0;
};

#endif