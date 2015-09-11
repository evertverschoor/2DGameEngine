#include "DirectXRenderer.h"
#include "Logger.h"
#include "StringConverter.h"


DirectXRenderer::DirectXRenderer(DirectXAssetManager* _assetmanager)
{
	ResourceManager = _assetmanager;
	Factory = NULL;
	RenderTarget = NULL;

	MotionBlurAngle = 0.0f;
	MotionBlurAmount = 0.0f;

	SetVirtualResolution(new Dimension(1920, 1080));
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
	// Start drawing on a blank bitmap
	bitmapRenderTarget->BeginDraw();
	WipeScreen(0, 0, 1);

	// Draw each entity in the scene
	for (int i = 0; i < _renderableScene->EntityCount(); i++)
	{
		DrawEntity(_renderableScene->GetEntity(i));
	}

	// End drawing here
	bitmapRenderTarget->EndDraw();

	// Get the bitmap that was just drawn
	ID2D1Bitmap* _bitmap;
	bitmapRenderTarget->GetBitmap(&_bitmap);

	// Send the bitmap to postprocessing
	PostProcess(_bitmap);

	// Release the temporary bitmap
	_bitmap->Release();

	return 1;
}

int DirectXRenderer::PostProcess(ID2D1Bitmap* _bitmap)
{
	ID2D1Image* _finalImage = _bitmap; // Put the bitmap into an image

	DeviceContext->BeginDraw();

	// Apply motion blur if turned on
	if (Settings->MotionBlur && MotionBlurAmount > 0.0f)
	{
		MotionBlur->SetInput(0, _finalImage);
		MotionBlur->SetValue(D2D1_DIRECTIONALBLUR_PROP_ANGLE, MotionBlurAngle);
		MotionBlur->SetValue(D2D1_DIRECTIONALBLUR_PROP_STANDARD_DEVIATION, MotionBlurAmount);
		MotionBlur->GetOutput(&_finalImage);
	}

	// Apply saturation if turned on
	if (Settings->Saturation)
	{
		Saturation->SetInput(0, _finalImage);
		Saturation.Get()->GetOutput(&_finalImage);
	}

	// Apply sharpening if turned on
	if (Settings->Sharpen)
	{
		Sharpen->SetInput(0, _finalImage);
		Sharpen.Get()->GetOutput(&_finalImage);
	}
	
	// Draw the processsed image to the backbuffer
	DeviceContext->DrawImage(_finalImage);

	// Draw FPS on the screen if turned on
	if (Settings->TrackFramerate) DrawFPS();
	
	DeviceContext->EndDraw();

	return 1;
}


int DirectXRenderer::WipeScreen(float _red, float _green, float _blue)
{
	bitmapRenderTarget->Clear(D2D1::ColorF(_red, _green, _blue));
	return 1;
}


int DirectXRenderer::DrawEntity(Entity* _entity)
{
	// Define the entity's bitmap to draw
	ID2D1Bitmap* _bitmap = ResourceManager->GetD2D1Bitmap(_entity);

	// Set the rotation for the bitmap, if necessary
	if (_entity->GetDirection() != 0)
	{
		bitmapRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(
			_entity->GetDirection(),
			D2D1::Point2F(
			_entity->GetPosition().X + (_bitmap->GetSize().width / 2),
			_entity->GetPosition().Y + (_bitmap->GetSize().height / 2)
			)
			)
			);
	}

	Position* _actualEntityPosition = GetActualDrawPosition(&_entity->GetPosition());
	Dimension* _actualEntitySize = GetActualDrawSize(new Dimension(_bitmap->GetSize().width, _bitmap->GetSize().height));

	// Draw the bitmap
	bitmapRenderTarget->DrawBitmap(
		ResourceManager->GetD2D1Bitmap(_entity),
		D2D1::RectF(
		_actualEntityPosition->X,
		_actualEntityPosition->Y,
		_actualEntityPosition->X + _actualEntitySize->Width,
		_actualEntityPosition->Y + _actualEntitySize->Height
		)
		);

	// Undo the rotation
	bitmapRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Identity()
		);

	return 1;
}

int DirectXRenderer::WriteText(std::string _text, Position* _position)
{
	Position* _actualTextPosition = GetActualDrawPosition(_position);

	RenderTarget->DrawTextW(
		StringConverter::Instance()->StringToWstring(_text).c_str(),
		_text.length(),
		DefaultTextFormat,
		D2D1::RectF(
		_actualTextPosition->X,
		_actualTextPosition->Y,
		_actualTextPosition->X + Settings->ScreenRes->Width,
		_actualTextPosition->Y + Settings->ScreenRes->Height
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
		D2D1::HwndRenderTargetProperties(*_windowhandle, D2D1::SizeU(Settings->ScreenRes->Width, Settings->ScreenRes->Height), Settings->Vsync ? D2D1_PRESENT_OPTIONS_NONE : D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&RenderTarget
		);

	if (FAILED(_result))
	{
		return -10;
	}

	// Create bitmapRenderTarget
	_result = RenderTarget->CreateCompatibleRenderTarget(&bitmapRenderTarget);

	if (FAILED(_result))
	{
		return -10;
	}

	SetDefaultTextFormat("Arial", 72.0f, RED, 1.0f);

	// Set the font family and size for the in-engine text
	_result = DWriteFactory->CreateTextFormat(
		L"Consolas",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		GetActualFontSize(40.0f),
		L"en-us",
		&EngineTextFormat
		);

	if (FAILED(_result))
	{
		return -20;
	}

	// Set the font color for the in-engine text
	_result = RenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f),
		&EngineTextBrush
		);

	if (FAILED(_result))
	{
		return -3;
	}

	// Get the device context from the rendertarget
	RenderTarget->QueryInterface(&DeviceContext);

	// Set up the motion blur effect
	if (Settings->MotionBlur)
	{
		DeviceContext->CreateEffect(CLSID_D2D1DirectionalBlur, &MotionBlur);
	}

	// Set up the sharpen effect
	if (Settings->Sharpen)
	{
		DeviceContext->CreateEffect(CLSID_D2D1ConvolveMatrix, &Sharpen);

		// Screen resolution around 720p
		if (Settings->ScreenRes->Height < 1000)
		{
			float matrix[9] =
			{
				-1, 0, -1,
				0, 10, 0,
				-1, 0, -1
			};

			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, matrix);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X, 3);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y, 3);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_DIVISOR, 7.0f);
		}

		// Screen resolution around 1080p/1440p
		else if (Settings->ScreenRes->Height > 1000 && Settings->ScreenRes->Height < 2000)
		{
			float matrix[25] =
			{
				-1, 0, 0, 0, -1,
				0, -1, 0, -1, 0,
				0, 0, 15, 0, 0,
				0, -1, 0, -1, 0,
				-1, 0, 0, 0, -1

			};

			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, matrix);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X, 5);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y, 5);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_DIVISOR, 8.0f);
		}

		// Screen resolution around 4k or higher
		else
		{
			float matrix[25] =
			{
				-2, 0, 0, 0, -2,
				0, -2, 0, -2, 0,
				0, 0, 25, 0, 0,
				0, -2, 0, -2, 0,
				-2, 0, 0, 0, -2

			};

			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, matrix);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X, 5);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y, 5);
			Sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_DIVISOR, 13.0f);
		}
	}

	// Set up the saturation effect
	if (Settings->Saturation)
	{
		DeviceContext->CreateEffect(CLSID_D2D1Saturation, &Saturation);
		Saturation->SetValue(D2D1_SATURATION_PROP_SATURATION, 1.8f);
	}

	PositionForFPS = GetActualDrawPosition(new Position(5, 5, 5));

	ResourceManager->SetRenderTarget(RenderTarget);

	return 1;
}


int DirectXRenderer::SetVideoSettings(VideoSettings* _settings)
{
	Settings = _settings;
	return 1;
}

int DirectXRenderer::SetMotionBlur(float _angle, float _amount)
{
	// Set the angle
	if (_angle > 0.0f && _angle < 360.0f) MotionBlurAngle = _angle;
	else
	{
		MotionBlurAngle = 0.0f;
	}

	// Set the amount
	if (_amount > 0.0f) MotionBlurAmount = _amount;
	else
	{
		MotionBlurAmount = 0.0f;
	}

	return 1;
}

int DirectXRenderer::SetDefaultTextFormat(std::string _fontname, float _fontsize, Color _color, float _transparency)
{
	// Set the font family and size.
	HRESULT _result = DWriteFactory->CreateTextFormat(
		StringConverter::Instance()->StringToWstring(_fontname).c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		GetActualFontSize(_fontsize),
		L"en-us",
		&DefaultTextFormat
		);

	if (FAILED(_result))
	{
		return -1;
	}

	// Set the font color.
	switch (_color)
	{
	case BLACK:
		_result = RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black, _transparency),
			&DefaultTextBrush
			); break;

	case WHITE:
		_result = RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White, _transparency),
			&DefaultTextBrush
			); break;

	case GRAY:
		_result = RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Gray, _transparency),
			&DefaultTextBrush
			); break;

	case RED:
		_result = RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red, _transparency),
			&DefaultTextBrush
			); break;

	case GREEN:
		_result = RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Green, _transparency),
			&DefaultTextBrush
			); break;

	case BLUE:
		_result = RenderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Blue, _transparency),
			&DefaultTextBrush
			); break;
	}

	if (FAILED(_result))
	{
		return -2;
	}

	return 1;
}

int DirectXRenderer::SetVirtualResolution(Dimension* _resolution)
{
	VirtualResolution = _resolution;
	return 1;
}

Position* DirectXRenderer::GetActualDrawPosition(Position* _position)
{
	// If the virtual resolution and actual resolution are the same, this doesnt need to happen.
	if (VirtualResolution->Height == Settings->ScreenRes->Height && VirtualResolution->Width == Settings->ScreenRes->Width)
	{
		return _position;
	}
	else
	{
		_position->X = (_position->X * Settings->ScreenRes->Width) / VirtualResolution->Width;
		_position->Y = (_position->Y * Settings->ScreenRes->Height) / VirtualResolution->Height;

		return _position;
	}
}

Dimension* DirectXRenderer::GetActualDrawSize(Dimension* _size)
{
	// If the virtual resolution and actual resolution are the same, this doesnt need to happen.
	if (VirtualResolution->Height == Settings->ScreenRes->Height && VirtualResolution->Width == Settings->ScreenRes->Width)
	{
		return _size;
	}
	else
	{
		_size->Width = (_size->Width * Settings->ScreenRes->Width) / VirtualResolution->Width;
		_size->Height = (_size->Height * Settings->ScreenRes->Height) / VirtualResolution->Height;
		return _size;
	}
}

float DirectXRenderer::GetActualFontSize(float _size)
{
	// If the virtual resolution and actual resolution are the same, this doesnt need to happen.
	if (VirtualResolution->Height == Settings->ScreenRes->Height && VirtualResolution->Width == Settings->ScreenRes->Width)
	{
		return _size;
	}
	else
	{
		_size = (_size * Settings->ScreenRes->Width) / VirtualResolution->Width;
		return _size;
	}
}

int DirectXRenderer::SetFPSToDraw(int _framerate)
{
	Framerate = _framerate;
	return 1;
}

int DirectXRenderer::DrawFPS()
{
	DeviceContext->DrawTextW(
		StringConverter::Instance()->IntToWString(Framerate).c_str(),
		StringConverter::Instance()->IntToWString(Framerate).length(),
		EngineTextFormat,
		D2D1::RectF(
		PositionForFPS->X,
		PositionForFPS->Y,
		PositionForFPS->X + Settings->ScreenRes->Width,
		PositionForFPS->Y + Settings->ScreenRes->Height
		),
		EngineTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP,
		DWRITE_MEASURING_MODE_NATURAL
		);

	return 1;
}