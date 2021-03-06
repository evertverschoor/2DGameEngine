#ifndef DIRECTXASSETLOADER_H
#define DIRECTXASSETLOADER_H

#include "Entity.h"
#include <wincodec.h>
#include <d2d1.h>

/// <summary>
/// The DirectX Asset Loader is used by the DirectX Asset Manager to load specific Direct2D assets.
/// </summary>
class DirectXAssetLoader
{
public:
	DirectXAssetLoader();
	~DirectXAssetLoader();

	/// <summary>
	/// Load a Direct2D Bitmap for an entity.
	/// @param1 The uri to the bitmap
	/// @param2 The bitmap which will be written to
	/// @param3 The render target from the DirectX Renderer
	/// </summary>
	int LoadD2DBitmap(std::wstring, ID2D1Bitmap**, ID2D1RenderTarget*);
private:
	IWICImagingFactory* imagingFactory;
	IWICBitmapDecoder* bitmapDecoder;
	IWICBitmapFrameDecode* bitmapSource;
	IWICStream* stream;
	IWICFormatConverter* formatConverter;
	IWICBitmapScaler* bitmapScaler;
};

#endif