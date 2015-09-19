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
	// For each entity
	for (int i = 0; i < _scene->EntityCount(); i++)
	{
		// And for each asset the entity has
		for (int j = 0; j < _scene->GetEntity(i)->AssetCount(); j++)
		{
			std::wstring _assetURI = _scene->GetEntity(i)->GetAssetUriByIndex(j);

			// Skip this asset if it's already loaded in
			if (assetList[_assetURI] != NULL) break;

			ID2D1Bitmap* _entityBitmap;
			int _result = loader->LoadD2DBitmap(_assetURI, &_entityBitmap, renderTarget);

			// Put NULL if bitmap loading failed
			assetList[_assetURI] = (_result == 1) ? _entityBitmap : NULL;
		}
	}

	// Load the scene background asset
	std::wstring _sceneAssetURI = _scene->GetBackgroundAssetURI();

	// Skip this asset if it's already loaded in
	if (assetList[_sceneAssetURI] != NULL) return 1;

	ID2D1Bitmap* _sceneBitmap;
	int _result = loader->LoadD2DBitmap(_sceneAssetURI, &_sceneBitmap, renderTarget);

	// Put NULL if bitmap loading failed
	assetList[_sceneAssetURI] = (_result == 1) ? _sceneBitmap : NULL;

	return 1;
}


int DirectXAssetManager::SetRenderTarget(ID2D1RenderTarget* _target)
{
	renderTarget = _target;
	return 1;
}


ID2D1Bitmap* DirectXAssetManager::GetD2D1BitmapForEntity(Entity* _entity)
{
	return assetList[_entity->GetCurrentAssetUri()];
}


int DirectXAssetManager::LoadSingleBitmap(std::string _uri)
{
	std::wstring _actualURI = StringConverter::Instance()->StringToWstring(_uri);

	// Skip this asset if it's already loaded in
	if (assetList[_actualURI] != NULL) return 1;

	ID2D1Bitmap* _bitmap;

	int _result = loader->LoadD2DBitmap(_actualURI, &_bitmap, renderTarget);

	// Put NULL if bitmap loading failed
	assetList[_actualURI] = (_result == 1) ? _bitmap : NULL;

	return 1;
}


ID2D1Bitmap* DirectXAssetManager::GetSingleBitmap(std::string _uri)
{
	return assetList[StringConverter::Instance()->StringToWstring(_uri)];
}


ID2D1Bitmap* DirectXAssetManager::GetSingleBitmap(std::wstring _uri)
{
	return assetList[_uri];
}