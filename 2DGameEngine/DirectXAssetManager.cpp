#include "DirectXAssetManager.h"
#include "Logger.h"


DirectXAssetManager::DirectXAssetManager()
{
	Loader = new DirectXAssetLoader();
}


DirectXAssetManager::~DirectXAssetManager()
{
	delete Loader;
}


int DirectXAssetManager::LoadScene(Scene* _scene)
{
	// Load the asset per entity in the scene
	for (int i = 0; i < _scene->EntityCount(); i++)
	{
		Entity* _entity = _scene->GetEntity(i);
		ID2D1Bitmap* _bitmap;
		int _result = Loader->LoadD2DBitmap(_entity, &_bitmap, RenderTarget);
		AssetList[_entity] = _bitmap;
	}

	return 1;
}


int DirectXAssetManager::SetRenderTarget(ID2D1RenderTarget* _target)
{
	RenderTarget = _target;
	return 1;
}


ID2D1Bitmap* DirectXAssetManager::GetD2D1Bitmap(Entity* _entity)
{
	return AssetList[_entity];
}