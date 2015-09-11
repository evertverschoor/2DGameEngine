#include "DirectXAssetLoader.h"


DirectXAssetLoader::DirectXAssetLoader()
{
	bitmapDecoder = NULL;
	bitmapSource = NULL;
	stream = NULL;
	formatConverter = NULL;
	bitmapScaler = NULL;

	HRESULT hr = CoInitialize(imagingFactory);

	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&imagingFactory));
}


DirectXAssetLoader::~DirectXAssetLoader()
{
	imagingFactory->Release();
	delete imagingFactory;
	bitmapDecoder->Release();
	delete bitmapDecoder;
	bitmapSource->Release();
	delete bitmapSource;
	stream->Release();
	delete stream;
	formatConverter->Release();
	delete formatConverter;
	bitmapScaler->Release();
	delete bitmapScaler;
}


int DirectXAssetLoader::LoadD2DBitmap(Entity* _entity, ID2D1Bitmap** _bitmap, ID2D1RenderTarget* _renderTarget)
{
	HRESULT hr = imagingFactory->CreateDecoderFromFilename(
		_entity->GetAssetURI().c_str(),
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&bitmapDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = bitmapDecoder->GetFrame(0, &bitmapSource);
	}
	else
	{
		return 0;
	}

	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = imagingFactory->CreateFormatConverter(&formatConverter);

	}
	else
	{
		return 0;
	}

	if (SUCCEEDED(hr))
	{
		hr = formatConverter->Initialize(
			bitmapSource,
			GUID_WICPixelFormat32bppPBGRA,
			WICBitmapDitherTypeNone,
			NULL,
			0.f,
			WICBitmapPaletteTypeMedianCut
			);
	}
	else
	{
		return 0;
	}

	if (SUCCEEDED(hr))
	{

		// Create a Direct2D bitmap from the WIC bitmap.
		hr = _renderTarget->CreateBitmapFromWicBitmap(
			formatConverter,
			NULL,
			_bitmap
			);
	}
	else
	{
		return 0;
	}

	return 1;
}