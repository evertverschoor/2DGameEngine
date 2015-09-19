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
	bitmapRenderTarget->Clear(D2D1::ColorF(0, 0, 1));

	// Draw the scene background image
	DrawSceneBackground(_renderableScene);

	// For each entity in the scene
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


int DirectXRenderer::DrawEntity(Entity* _entity)
{
	// Define the entity's bitmap to draw
	ID2D1Bitmap* _bitmap = resourceManager->GetD2D1BitmapForEntity(_entity);

	// No asset exists for the entity, return
	if (NULL == _bitmap) return 0;

	// calculate the actual entity size and position
	GetActualDrawPosition(_entity->GetPosition(), &actualEntityPositionDump);
	GetActualDrawSize(_bitmap->GetSize().width, _bitmap->GetSize().height, &actualEntitySizeDump);

	// Set the rotation for the bitmap, if necessary
	if (_entity->GetDirection() != 0)
	{
		bitmapRenderTarget->SetTransform(
			D2D1::Matrix3x2F::Rotation(
			_entity->GetDirection(),
			D2D1::Point2F(
			actualEntityPositionDump.X + (actualEntitySizeDump.width / 2),
			actualEntityPositionDump.Y + (actualEntitySizeDump.height / 2)
			)
			)
			);
	}

	// Draw the bitmap
	bitmapRenderTarget->DrawBitmap(
		_bitmap,
		D2D1::RectF(
		actualEntityPositionDump.X,
		actualEntityPositionDump.Y,
		actualEntityPositionDump.X + actualEntitySizeDump.width,
		actualEntityPositionDump.Y + actualEntitySizeDump.height
		)
		);

	// Undo the rotation
	bitmapRenderTarget->SetTransform(
		D2D1::Matrix3x2F::Identity()
		);

	return 1;
}


int DirectXRenderer::DrawSceneBackground(Scene* _scene)
{
	// Define the entity's bitmap to draw
	ID2D1Bitmap* _bitmap = resourceManager->GetSingleBitmap(_scene->GetBackgroundAssetURI());

	// If no background was defined for the scene, return.
	if (NULL == _bitmap) return 0;

	// Calculate the actual background size
	GetActualDrawSize(_bitmap->GetSize().width, _bitmap->GetSize().height, &actualBackgroundSizeDump);

	// Determine where to draw the background based on the background type
	switch (*_scene->GetBackgroundType())
	{
		case PERSIST:
			actualBackgroundPositionDump = defaultBackgroundPosition;;
			break;
		case MOVE:
			GetActualDrawPosition(&defaultBackgroundPosition, &actualBackgroundPositionDump);
			break;
		case SLOW_MOVE:
			GetActualDrawPosition(&defaultBackgroundPosition, &actualBackgroundPositionDump);
			actualBackgroundPositionDump.X /= 2;
			actualBackgroundPositionDump.Y /= 2;
			break;
		default:
			actualBackgroundPositionDump = defaultBackgroundPosition;
			break;
	}

	// Draw the bitmap
	bitmapRenderTarget->DrawBitmap(
		_bitmap,
		D2D1::RectF(
		actualBackgroundPositionDump.X,
		actualBackgroundPositionDump.Y,
		actualBackgroundPositionDump.X + actualBackgroundSizeDump.width,
		actualBackgroundPositionDump.Y + actualBackgroundSizeDump.height
		)
		);

	return 1;
}

int DirectXRenderer::WriteText(std::string _text, Position* _position)
{
	GetActualDrawPosition(_position, &actualTextPositionDump);

	renderTarget->DrawTextW(
		StringConverter::Instance()->StringToWstring(_text).c_str(),
		_text.length(),
		defaultTextFormat,
		D2D1::RectF(
		actualTextPositionDump.X,
		actualTextPositionDump.Y,
		actualTextPositionDump.X + settings->screenRes->width,
		actualTextPositionDump.Y + settings->screenRes->height
		),
		defaultTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP,
		DWRITE_MEASURING_MODE_NATURAL
		);

	return 1;
}


int DirectXRenderer::DrawEngineSplash(float _red, float _green, float _blue)
{
	// Prep screen
	renderTarget->BeginDraw();
	renderTarget->Clear(D2D1::ColorF(_red, _green, _blue));

	// Get the loaded splash screen bitmap
	ID2D1Bitmap* _bitmap = resourceManager->GetSingleBitmap("Assets/Engine/splash_screen.png");

	// Bitmap wasn't properly loaded or doesn't exist, return
	if (NULL == _bitmap) return 0;

	// Calculate the actual bitmap size, we'll just use the entity size dump
	GetActualDrawSize(_bitmap->GetSize().width, _bitmap->GetSize().height, &actualEntitySizeDump);

	// Calculate the draw position, always draw at the center of the screen
	int _posX = (settings->screenRes->width / 2) - (actualEntitySizeDump.width / 2);
	int _posY = (settings->screenRes->height / 2) - (actualEntitySizeDump.height / 2);

	// Draw the bitmap
	renderTarget->DrawBitmap(
		_bitmap,
		D2D1::RectF(
		_posX,
		_posY,
		_posX + actualEntitySizeDump.width,
		_posY + actualEntitySizeDump.height
		)
		);

	// Finalize
	renderTarget->EndDraw();

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

	SetDefaultTextFormat("Segoe UI", 244.0f, WHITE, 1.0f);

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

	Position* _fpsPos = new Position(5, 5, 5);

	GetActualDrawPosition(_fpsPos, &positionForFPS);

	delete _fpsPos;

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

int DirectXRenderer::GetActualDrawPosition(Position* _position, Position* _dump)
{
	// subtract the camera coordinates
	_dump->X = _position->X - camera->GetPosition()->X;
	_dump->Y = _position->Y - camera->GetPosition()->Y;

	// adjust the position to the actual resolution
	_dump->X = (_dump->X * settings->screenRes->width) / virtualResolution->width;
	_dump->Y = (_dump->Y * settings->screenRes->height) / virtualResolution->height;

	return 1;
}

int DirectXRenderer::GetActualDrawSize(int _width, int _height, Dimension* _dump)
{
	_dump->width = (_width * settings->screenRes->width) / virtualResolution->width;
	_dump->height = (_height * settings->screenRes->height) / virtualResolution->height;

	return 1;
}

float DirectXRenderer::GetActualFontSize(float _size)
{
	_size = (_size * settings->screenRes->width) / virtualResolution->width;

	return _size;
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
		positionForFPS.X,
		positionForFPS.Y,
		positionForFPS.X + settings->screenRes->width,
		positionForFPS.Y + settings->screenRes->height
		),
		engineTextBrush,
		D2D1_DRAW_TEXT_OPTIONS_CLIP,
		DWRITE_MEASURING_MODE_NATURAL
		);

	return 1;
}