#ifndef DIRECTXRENDERER_H
#define DIRECTXRENDERER_H

#include "Renderer.h"
#include "Scene.h"
#include "Entity.h"
#include "VideoSettings.h"
#include "DirectXAssetManager.h"
#include "Position.h"
#include <d2d1.h>
#include <dwrite.h>

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
	int WriteText(std::string, Position*);

	int SetVideoSettings(VideoSettings*);
	int SetDefaultTextFormat(std::string, float);
private:
	ID2D1Factory* Factory;
	IDWriteFactory* DWriteFactory;
	ID2D1HwndRenderTarget* RenderTarget;
	VideoSettings* Settings;
	DirectXAssetManager* ResourceManager;
	IDWriteTextFormat* DefaultTextFormat;
	ID2D1SolidColorBrush* DefaultTextBrush;

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