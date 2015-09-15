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
		int _result = loader->LoadD2DBitmap(_entity->GetAssetURI(), &_bitmap, renderTarget);
		assetList[_entity] = _bitmap;
	}

	return 1;
}


int DirectXAssetManager::SetRenderTarget(ID2D1RenderTarget* _target)
{
	renderTarget = _target;
	return 1;
}


ID2D1Bitmap* DirectXAssetManager::GetD2D1BitmapForEntity(Entity* _entity)
{
	return assetList[_entity];
}


int DirectXAssetManager::LoadSingleBitmap(std::string _uri)
{
	ID2D1Bitmap* _bitmap;

	loader->LoadD2DBitmap(StringConverter::Instance()->StringToWstring(_uri), &_bitmap, renderTarget);

	singleBitmapList[_uri] = _bitmap;

	return 1;
}


ID2D1Bitmap* DirectXAssetManager::GetSingleBitmap(std::string _uri)
{
	return singleBitmapList[_uri];
}