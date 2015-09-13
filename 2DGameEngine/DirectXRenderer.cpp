#include "DirectXRenderer.h"


DirectXRenderer::DirectXRenderer(DirectXAssetManager* _assetmanager)
{
	resourceManager = _assetmanager;
	factory = NULL;
	renderTarget = NULL;
}


DirectXRenderer::~DirectXRenderer()
{
	if (factory) factory->Release();
	if (renderTarget) renderTarget->Release();

	delete factory;
	delete renderTarget;
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

	deviceContext->BeginDraw();

	// Apply saturation if turned on
	if (settings->saturate)
	{
		saturate->SetInput(0, _finalImage);
		saturate.Get()->GetOutput(&_finalImage);
	}

	// Apply motion blur if turned on
	if (settings->motionBlur && gfx->GetMotionBlurAmount() > 0.0f)
	{
		motionBlur->SetInput(0, _finalImage);
		motionBlur->SetValue(D2D1_DIRECTIONALBLUR_PROP_ANGLE, gfx->GetMotionBlurAngle());
		motionBlur->SetValue(D2D1_DIRECTIONALBLUR_PROP_STANDARD_DEVIATION, gfx->GetMotionBlurAmount());
		motionBlur->GetOutput(&_finalImage);

		// Reset the motion blur data after we're done
		gfx->SetMotionBlur(0.0f, 0.0f);
	}

	// Apply sharpening if turned on
	if (settings->sharpen)
	{
		sharpen->SetInput(0, _finalImage);
		sharpen.Get()->GetOutput(&_finalImage);
	}

	// Apply brightening if turned on
	if (settings->brighten)
	{
		brighten->SetInput(0, _finalImage);
		brighten.Get()->GetOutput(&_finalImage);
	}

	// Draw the processsed image to the backbuffer
	deviceContext->DrawImage(_finalImage);

	// Draw FPS on the screen if turned on
	if (settings->trackFramerate) DrawFPS();
	
	deviceContext->EndDraw();

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
	ID2D1Bitmap* _bitmap = resourceManager->GetD2D1Bitmap(_entity);

	// Set the rotation for the bitmap, if necessary
	if (_entity->GetDirection() != 0)
	{
		bitmapRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(
			_entity->GetDirection(),
			D2D1::Point2F(
			_entity->GetPosition().X + (_bitmap->GetSize().width / 2) - camera->GetPosition()->X,
			_entity->GetPosition().Y + (_bitmap->GetSize().height / 2) - camera->GetPosition()->Y
			)
			)
			);
	}

	Position* _actualEntityPosition = GetActualDrawPosition(&_entity->GetPosition());
	Dimension* _actualEntitySize = GetActualDrawSize(new Dimension(_bitmap->GetSize().width, _bitmap->GetSize().height));

	// Draw the bitmap
	bitmapRenderTarget->DrawBitmap(
		resourceManager->GetD2D1Bitmap(_entity),
		D2D1::RectF(
		_actualEntityPosition->X,
		_actualEntityPosition->Y,
		_actualEntityPosition->X + _actualEntitySize->width,
		_actualEntityPosition->Y + _actualEntitySize->height
		)
		);

	// Undo the rotation
	bitmapRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Identity()
		);

	delete _actualEntitySize;

	return 1;
}

int DirectXRenderer::WriteText(std::string _text, Position* _position)
{
	Position* _actualTextPosition = GetActualDrawPosition(_position);

	renderTarget->DrawTextW(
		StringConverter::Instance()->StringToWstring(_text).c_str(),
		_text.length(),
		defaultTextFormat,
		D2D1::RectF(
		_actualTextPosition->X,
		_actualTextPosition->Y,
		_actualTextPosition->X + settings->screenRes->width,
		_actualTextPosition->Y + settings->screenRes->height
		),
		defaultTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP,
		DWRITE_MEASURING_MODE_NATURAL
		);

	return 1;
}


int DirectXRenderer::Init(HWND* _windowhandle)
{
	// Create D2D factory
	HRESULT _result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create D2D1Factory");
		return -1;
	}

	// Create DirectWrite factory
	_result = DWriteCreateFactory(
		DWRITE_FACTORY_TYPE_SHARED,
		__uuidof(IDWriteFactory),
		reinterpret_cast<IUnknown**>(&dWriteFactory)
		);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create IDWriteFactory");
		return -2;
	}

	RECT _rect;
	GetClientRect(*_windowhandle, &_rect);

	// Create the render target
	_result = factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		D2D1::HwndRenderTargetProperties(*_windowhandle, D2D1::SizeU(settings->screenRes->width, settings->screenRes->height), settings->vsync ? D2D1_PRESENT_OPTIONS_NONE : D2D1_PRESENT_OPTIONS_IMMEDIATELY),
		&renderTarget
		);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create HwndRenderTarget");
		return -3;
	}

	// Create bitmapRenderTarget
	_result = renderTarget->CreateCompatibleRenderTarget(&bitmapRenderTarget);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create BitmapRenderTarget");
		return -4;
	}

	SetDefaultTextFormat("Arial", 72.0f, RED, 1.0f);

	// Set the font family and size for the in-engine text
	_result = dWriteFactory->CreateTextFormat(
		L"Consolas",
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		GetActualFontSize(40.0f),
		L"en-us",
		&engineTextFormat
		);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create IDWriteTextFormat");
		return -5;
	}

	// Set the font color for the in-engine text
	_result = renderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::Yellow, 1.0f),
		&engineTextBrush
		);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create ID2D1SolidColorBrush");
		return -6;
	}

	// Get the device context from the rendertarget
	renderTarget->QueryInterface(&deviceContext);

	// Set up the motion blur effect
	if (settings->motionBlur)
	{
		deviceContext->CreateEffect(CLSID_D2D1DirectionalBlur, &motionBlur);
	}

	// Set up the sharpen effect
	if (settings->sharpen)
	{
		deviceContext->CreateEffect(CLSID_D2D1ConvolveMatrix, &sharpen);

		// Screen resolution around 720p
		if (settings->screenRes->height < 1000)
		{
			float _matrix[9] =
			{
				-1, 0, -1,
				0, 10, 0,
				-1, 0, -1
			};

			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, _matrix);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X, 3);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y, 3);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_DIVISOR, 6.0f);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_PRESERVE_ALPHA, TRUE);
		}

		// Screen resolution around 1080p/1440p
		else if (settings->screenRes->height > 1000 && settings->screenRes->height < 2000)
		{
			float _matrix[25] =
			{
				-1, 0, 0, 0, -1,
				0, -1, 0, -1, 0,
				0, 0, 15, 0, 0,
				0, -1, 0, -1, 0,
				-1, 0, 0, 0, -1

			};

			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, _matrix);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X, 5);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y, 5);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_DIVISOR, 7.0f);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_PRESERVE_ALPHA, TRUE);
		}

		// Screen resolution around 4k or higher
		else
		{
			float _matrix[25] =
			{
				-2, 0, 0, 0, -2,
				0, -2, 0, -2, 0,
				0, 0, 25, 0, 0,
				0, -2, 0, -2, 0,
				-2, 0, 0, 0, -2

			};

			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_MATRIX, _matrix);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_X, 5);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_KERNEL_SIZE_Y, 5);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_DIVISOR, 9.0f);
			sharpen->SetValue(D2D1_CONVOLVEMATRIX_PROP_PRESERVE_ALPHA, TRUE);
		}
	}

	// Set up the saturation effect
	if (settings->saturate)
	{
		deviceContext->CreateEffect(CLSID_D2D1Saturation, &saturate);
		saturate->SetValue(D2D1_SATURATION_PROP_SATURATION, 1.8f);
	}

	// Set up the brighten effect
	if (settings->brighten)
	{
		deviceContext->CreateEffect(CLSID_D2D1Brightness, &brighten);
		brighten->SetValue(D2D1_BRIGHTNESS_PROP_BLACK_POINT, D2D1::Vector2F(0.0f, 0.2f));
	}

	positionForFPS = GetActualDrawPosition(new Position(5, 5, 5));

	resourceManager->SetRenderTarget(renderTarget);

	return 1;
}


int DirectXRenderer::SetVideoSettings(VideoSettings* _settings)
{
	settings = _settings;
	return 1;
}


int DirectXRenderer::SetCamera(Camera* _camera)
{
	camera = _camera;
	return 1;
}


int DirectXRenderer::SetGFXController(GFXController* _gfx)
{
	gfx = _gfx;
	return 1;
}


int DirectXRenderer::SetDefaultTextFormat(std::string _fontname, float _fontsize, Color _color, float _transparency)
{
	// Set the font family and size.
	HRESULT _result = dWriteFactory->CreateTextFormat(
		StringConverter::Instance()->StringToWstring(_fontname).c_str(),
		NULL,
		DWRITE_FONT_WEIGHT_REGULAR,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		GetActualFontSize(_fontsize),
		L"en-us",
		&defaultTextFormat
		);

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create Default Text Format");
		return -1;
	}

	// Set the font color.
	switch (_color)
	{
	case BLACK:
		_result = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Black, _transparency),
			&defaultTextBrush
			); break;

	case WHITE:
		_result = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::White, _transparency),
			&defaultTextBrush
			); break;

	case GRAY:
		_result = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Gray, _transparency),
			&defaultTextBrush
			); break;

	case RED:
		_result = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Red, _transparency),
			&defaultTextBrush
			); break;

	case GREEN:
		_result = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Green, _transparency),
			&defaultTextBrush
			); break;

	case BLUE:
		_result = renderTarget->CreateSolidColorBrush(
			D2D1::ColorF(D2D1::ColorF::Blue, _transparency),
			&defaultTextBrush
			); break;
	}

	if (FAILED(_result))
	{
		Logger::Instance()->Log("\nFailed to create Default Text Brush");
		return -2;
	}

	return 1;
}

int DirectXRenderer::SetVirtualResolution(Dimension* _resolution)
{
	virtualResolution = _resolution;
	return 1;
}

Position* DirectXRenderer::GetActualDrawPosition(Position* _position)
{
	// subtract the camera coordinates
	_position->X -= camera->GetPosition()->X;
	_position->Y -= camera->GetPosition()->Y;

	// If the virtual resolution and actual resolution are the same, this doesnt need to happen.
	if (virtualResolution->height == settings->screenRes->height && virtualResolution->width == settings->screenRes->width)
	{
		return _position;
	}
	else
	{
		_position->X = (_position->X * settings->screenRes->width) / virtualResolution->width;
		_position->Y = (_position->Y * settings->screenRes->height) / virtualResolution->height;

		return _position;
	}
}

Dimension* DirectXRenderer::GetActualDrawSize(Dimension* _size)
{
	// If the virtual resolution and actual resolution are the same, this doesnt need to happen.
	if (virtualResolution->height == settings->screenRes->height && virtualResolution->width == settings->screenRes->width)
	{
		return _size;
	}
	else
	{
		_size->width = (_size->width * settings->screenRes->width) / virtualResolution->width;
		_size->height = (_size->height * settings->screenRes->height) / virtualResolution->height;
		return _size;
	}
}

float DirectXRenderer::GetActualFontSize(float _size)
{
	// If the virtual resolution and actual resolution are the same, this doesnt need to happen.
	if (virtualResolution->height == settings->screenRes->height && virtualResolution->width == settings->screenRes->width)
	{
		return _size;
	}
	else
	{
		_size = (_size * settings->screenRes->width) / virtualResolution->width;
		return _size;
	}
}

int DirectXRenderer::SetFPSToDraw(int _framerate)
{
	framerate = _framerate;
	return 1;
}

int DirectXRenderer::DrawFPS()
{
	deviceContext->DrawTextW(
		StringConverter::Instance()->IntToWString(framerate).c_str(),
		StringConverter::Instance()->IntToWString(framerate).length(),
		engineTextFormat,
		D2D1::RectF(
		positionForFPS->X,
		positionForFPS->Y,
		positionForFPS->X + settings->screenRes->width,
		positionForFPS->Y + settings->screenRes->height
		),
		engineTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP,
		DWRITE_MEASURING_MODE_NATURAL
		);

	return 1;
}