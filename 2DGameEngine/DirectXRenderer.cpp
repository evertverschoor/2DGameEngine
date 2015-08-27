#include "DirectXRenderer.h"
#include "Logger.h"
#include "StringConverter.h"


DirectXRenderer::DirectXRenderer(DirectXAssetManager* _assetmanager)
{
	ResourceManager = _assetmanager;
	Factory = NULL;
	RenderTarget = NULL;
}


DirectXRenderer::~DirectXRenderer()
{
	if (Factory) Factory->Release();
	if (RenderTarget) RenderTarget->Release();

	delete Factory;
	delete RenderTarget;
}


int DirectXRenderer::Render(Scene* _renderableScene)
{
	// Start drawing on a blank canvas
	RenderTarget->BeginDraw();
	WipeScreen(0,0,1);

	// Draw each entity in the scene
	for (int i = 0; i < _renderableScene->EntityCount(); i++)
	{
		DrawEntity(_renderableScene->GetEntity(i));
	}

	WriteText("Text here!", new Position(10,10,2));

	// End drawing here
	RenderTarget->EndDraw();

	return 1;
}


int DirectXRenderer::WipeScreen(float _red, float _green, float _blue)
{
	RenderTarget->Clear(D2D1::ColorF(_red, _green, _blue));
	return 1;
}


int DirectXRenderer::DrawEntity(Entity* _entity)
{
	// Define the entity's bitmap to draw
	ID2D1Bitmap* _bitmap = ResourceManager->GetD2D1Bitmap(_entity);

	// Set the rotation for the bitmap, if necessary
	if (_entity->GetDirection() != 0)
	{
		RenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(
				_entity->GetDirection(), 
				D2D1::Point2F(
					_entity->GetPosition().X + (_bitmap->GetSize().width / 2),
					_entity->GetPosition().Y + (_bitmap->GetSize().height / 2)
				)
			)
		);
	}

	// Draw the bitmap
	RenderTarget->DrawBitmap(
		ResourceManager->GetD2D1Bitmap(_entity),
		D2D1::RectF(
			_entity->GetPosition().X,
			_entity->GetPosition().Y,
			_entity->GetPosition().X + _bitmap->GetSize().width,
			_entity->GetPosition().Y + _bitmap->GetSize().height
		)
	);

	// Undo the rotation
	RenderTarget->SetTransform(
		D2D1::Matrix3x2F::Identity()
	);

	return 1;
}

int DirectXRenderer::WriteText(std::string _text, Position* _position)
{
	RenderTarget->DrawTextW (
		StringConverter::Instance()->StringToWstring(_text).c_str(),
		_text.length(),
		DefaultTextFormat,
		D2D1::RectF(
		_position->X,
		_position->Y,
		_position->X + Settings->ScreenRes->Width,
		_position->Y + Settings->ScreenRes->Height
		),
		DefaultTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP,
		DWRITE_MEASURING_MODE_NATURAL
		);

	return 1;
}


int DirectXRenderer::Init(HWND* _windowhandle)
{
	// Create D2D factory
	HRESULT _result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &Factory);

	if (FAILED(_result))
	{
		return -1;
	}

	// Create DirectWrite factory
	_result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&DWriteFactory)
		);

	if (FAILED(_result))
	{
		return -2;
	}

	RECT _rect;
	GetClientRect(*_windowhandle, &_rect);

	// Create the render target
	_result = Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(*_windowhandle, D2D1::SizeU(Settings->ScreenRes->Width, Settings->ScreenRes->Height)),
		&RenderTarget
	);

	if (FAILED(_result))
	{
		return -10;
	}

	// Create the default text format
	_result = DWriteFactory->CreateTextFormat(
		L"Gabriola",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		72.0f,
		L"en-us",
		&DefaultTextFormat
		);

	if (FAILED(_result))
	{
		return -20;
	}

	_result = RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Black, 1.0f),
		&DefaultTextBrush
		);

	ResourceManager->SetRenderTarget(RenderTarget);

	return 1;
}


int DirectXRenderer::SetVideoSettings(VideoSettings* _settings)
{
	Settings = _settings;
	return 1;
}

int DirectXRenderer::SetDefaultTextFormat(std::string _fontname, float _fontsize)
{
	HRESULT _result = DWriteFactory->CreateTextFormat(
		StringConverter::Instance()->StringToWstring(_fontname).c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		_fontsize,
		L"en-us",
		&DefaultTextFormat
		);
	return 1;
}