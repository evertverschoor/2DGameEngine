#ifndef DIRECTXASSETLOADER_H
#define DIRECTXASSETLOADER_H

#include "Entity.h"
#include <d2d1.h>
#include <wincodec.h>

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
	/// @param1 The entity which the asset belongs to
	/// @param2 The bitmap which will be written to
	/// @param3 The render target from the DirectX Renderer
	/// </summary>
	int LoadD2DBitmap(Entity*, ID2D1Bitmap**, ID2D1RenderTarget*);
private:
	IWICImagingFactory* ImagingFactory;
	IWICBitmapDecoder *pDecoder;
	IWICBitmapFrameDecode *pSource;
	IWICStream *pStream;
	IWICFormatConverter *pConverter;
	IWICBitmapScaler *pScaler;
};

#endif