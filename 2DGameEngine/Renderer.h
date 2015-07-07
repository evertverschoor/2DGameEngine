#ifndef RENDERER_H
#define RENDERER_H

#include "Scene.h"
#include "Windows.h"
#include "VideoSettings.h"

/// <summary>
/// The rendere is an interface that will be realized by a DirectX Renderer.
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
	/// Initialize the renderer with a window handle.
	/// </summary>
	virtual int Init(HWND*) = 0;

	/// <summary>
	/// Set the video settings for the render quality.
	/// </summary>
	virtual int SetVideoSettings(VideoSettings*) = 0;
};

#endif