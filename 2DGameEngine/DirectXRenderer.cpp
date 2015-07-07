#include "DirectXRenderer.h"
#include "Logger.h"


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


int DirectXRenderer::Init(HWND* _windowhandle)
{
	HRESULT _result = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &Factory);

	if (FAILED(_result))
	{
		return -1;
	}

	RECT _rect;
	GetClientRect(*_windowhandle, &_rect);

	_result = Factory->CreateHwndRenderTarget(
		D2D1::RenderTargetProperties(),
		//D2D1::HwndRenderTargetProperties(*_windowhandle, D2D1::SizeU(_rect.right, _rect.bottom)),
		D2D1::HwndRenderTargetProperties(*_windowhandle, D2D1::SizeU(Settings->ScreenRes->Width, Settings->ScreenRes->Height)),
		&RenderTarget
	);

	if (FAILED(_result))
	{
		return -10;
	}

	ResourceManager->SetRenderTarget(RenderTarget);

	return 1;
}


int DirectXRenderer::SetVideoSettings(VideoSettings* _settings)
{
	Settings = _settings;
	return 1;
}