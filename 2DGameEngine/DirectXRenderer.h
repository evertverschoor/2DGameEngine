#ifndef DIRECTXRENDERER_H
#define DIRECTXRENDERER_H

#include "Renderer.h"
#include "Scene.h"
#include "Entity.h"
#include "VideoSettings.h"
#include "DirectXAssetManager.h"
#include "Position.h"
#include "Color.h"
#include "Dimension.h"
#include "Logger.h"
#include "StringConverter.h"
#include <d2d1.h>
#include <dwrite.h>
#include <d2d1effects.h>
#include <d2d1_1.h>
#include <wrl.h>

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
	int DrawEngineSplash(float, float, float);

	int SetVideoSettings(VideoSettings*);
	int SetDefaultTextFormat(std::string, float, Color, float);
	int SetVirtualResolution(Dimension*);
	int SetFPSToDraw(int);
	int SetCamera(Camera*);
	int SetGFXController(GFXController*);
private:
	// DirectX objects
	ID2D1Factory* factory;
	IDWriteFactory* dWriteFactory;
	ID2D1HwndRenderTarget* renderTarget;
	ID2D1BitmapRenderTarget* bitmapRenderTarget;
	ID2D1DeviceContext* deviceContext;

	// Postproccessing effects
	Microsoft::WRL::ComPtr<ID2D1Effect> motionBlur;
	Microsoft::WRL::ComPtr<ID2D1Effect> sharpen;
	Microsoft::WRL::ComPtr<ID2D1Effect> saturate;
	Microsoft::WRL::ComPtr<ID2D1Effect> brighten;

	// Text appearance objects for in-game text
	IDWriteTextFormat* defaultTextFormat;
	ID2D1SolidColorBrush* defaultTextBrush;

	// Text appearance objects for in-engine text
	IDWriteTextFormat* engineTextFormat;
	ID2D1SolidColorBrush* engineTextBrush;
	Position* positionForFPS;

	// Engine objects
	VideoSettings* settings;
	DirectXAssetManager* resourceManager;
	Dimension* virtualResolution;
	Camera* camera;
	GFXController* gfx;
	int framerate;
	
	/// <summary>
	/// Execute any post process effects and draw the image to the screen.
	/// </summary>
	int PostProcess(ID2D1Bitmap*);

	/// <summary>
	/// Draw an entity to the screen.
	/// </summary>
	int DrawEntity(Entity*);

	/// <summary>
	/// Calculates the actual draw position for an entity if the virtual resolution is different from the actual resolution.
	/// </summary>
	Position* GetActualDrawPosition(Position*);

	/// <summary>
	/// Calculates the actual draw size for an entity if the virtual resolution is different from the actual resolution.
	/// </summary>
	Dimension* GetActualDrawSize(Dimension*);

	/// <summary>
	/// Calculates the actual font size for a piece of text if the virtual resolution is different from the actual resolution.
	/// </summary>
	float GetActualFontSize(float);

	/// <summary>
	/// Draw the framerate on the screen.
	/// </summary>
	int DrawFPS();
};

#endif