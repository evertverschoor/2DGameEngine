#ifndef DIRECTXASSETMANAGER_H
#define DIRECTXASSETMANAGER_H

#include "AssetManager.h"
#include "Scene.h"
#include "DirectXAssetLoader.h"
#include "StringConverter.h"
#include "Logger.h"
#include <d2d1.h>
#include <map>

/// <summary>
/// The specialized DirectX Asset Manager realizes the AssetManger interface so the DirectX Renderer can use it
/// </summary>
class DirectXAssetManager : public AssetManager
{
public:
	DirectXAssetManager();
	~DirectXAssetManager();

	int LoadScene(Scene*);
	int LoadSingleBitmap(std::string);

	/// <summary>
	/// Set the render target from the DirectX Renderer.
	/// </summary>
	int SetRenderTarget(ID2D1RenderTarget*);

	/// <summary>
	/// Get the Direct2D bitmap that belongs to an entity.
	/// </summary>
	ID2D1Bitmap* GetD2D1BitmapForEntity(Entity*);

	/// <summary>
	/// Get a bitmap that doesnt belong to an entity, but has been loaded in.
	/// </summary>
	ID2D1Bitmap* GetSingleBitmap(std::string);

	ID2D1Bitmap* GetSingleBitmap(std::wstring);

private:
	DirectXAssetLoader* loader;
	ID2D1RenderTarget* renderTarget;
	std::map<std::wstring, ID2D1Bitmap*> assetList;
};

#endif