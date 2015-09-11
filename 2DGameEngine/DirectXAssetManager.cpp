#include "DirectXAssetManager.h"


DirectXAssetManager::DirectXAssetManager()
{
	loader = new DirectXAssetLoader();
}


DirectXAssetManager::~DirectXAssetManager()
{
	delete loader;
}


int DirectXAssetManager::LoadScene(Scene* _scene)
{
	// Load the asset per entity in the scene
	for (int i = 0; i < _scene->EntityCount(); i++)
	{
		Entity* _entity = _scene->GetEntity(i);
		ID2D1Bitmap* _bitmap;
		int _result = loader->LoadD2DBitmap(_entity, &_bitmap, renderTarget);
		assetList[_entity] = _bitmap;
	}

	return 1;
}


int DirectXAssetManager::SetRenderTarget(ID2D1RenderTarget* _target)
{
	renderTarget = _target;
	return 1;
}


ID2D1Bitmap* DirectXAssetManager::GetD2D1Bitmap(Entity* _entity)
{
	return assetList[_entity];
}