#ifndef DIRECTXRENDERER_H
#define DIRECTXRENDERER_H

#include "Renderer.h"
#include "Scene.h"
#include "Entity.h"
#include "VideoSettings.h"
#include "DirectXAssetManager.h"
#include <d2d1.h>

/// <summary>
/// The DirectX Renderer that realizes the Renderer interface.
/// Responsible for rendering to the main window.
/// </summary>
class DirectXRenderer : public Renderer
{
public:
	DirectXRenderer(DirectXAssetManager*);
	~DirectXRenderer();
	int Render(Scene*);
	int Init(HWND*);
	int SetVideoSettings(VideoSettings*);
private:
	ID2D1Factory* Factory;
	ID2D1HwndRenderTarget* RenderTarget;
	VideoSettings* Settings;
	DirectXAssetManager* ResourceManager;

	/// <summary>
	/// Wipe the screen empty to a specified RGB colour.
	/// </summary>
	int WipeScreen(float, float, float);

	/// <summary>
	/// Draw an entity to the screen.
	/// </summary>
	int DrawEntity(Entity*);
};

#endif