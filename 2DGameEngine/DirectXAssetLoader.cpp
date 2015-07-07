#include "DirectXAssetLoader.h"
#include "Logger.h"


DirectXAssetLoader::DirectXAssetLoader()
{
	pDecoder = NULL;
	pSource = NULL;
	pStream = NULL;
	pConverter = NULL;
	pScaler = NULL;

	HRESULT hr = CoInitialize(ImagingFactory);

	hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&ImagingFactory));
}


DirectXAssetLoader::~DirectXAssetLoader()
{
	ImagingFactory->Release();
	delete ImagingFactory;
	pDecoder->Release();
	delete pDecoder;
	pSource->Release();
	delete pSource;
	pStream->Release();
	delete pStream;
	pConverter->Release();
	delete pConverter;
	pScaler->Release();
	delete pScaler;
}


int DirectXAssetLoader::LoadD2DBitmap(Entity* _entity, ID2D1Bitmap** _bitmap, ID2D1RenderTarget* _renderTarget)
{
	HRESULT hr = ImagingFactory->CreateDecoderFromFilename(
		_entity->GetAssetURI().c_str(),
		NULL,
		GENERIC_READ,
		WICDecodeMetadataCacheOnLoad,
		&pDecoder
	);

	if (SUCCEEDED(hr))
	{
		// Create the initial frame.
		hr = pDecoder->GetFrame(0, &pSource);
	}
	else
	{
		return 0;
	}

	if (SUCCEEDED(hr))
	{

		// Convert the image format to 32bppPBGRA
		// (DXGI_FORMAT_B8G8R8A8_UNORM + D2D1_ALPHA_MODE_PREMULTIPLIED).
		hr = ImagingFactory->CreateFormatConverter(&pConverter);

	}
	else
	{
		return 0;
	}

	if (SUCCEEDED(hr))
	{
		hr = pConverter->Initialize(
			pSource,
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
			pConverter,
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