#ifndef INCLUDED_ENGINE_TERRAINCOMPONENT_H
#define INCLUDED_ENGINE_TERRAINCOMPONENT_H

#include "Component.h"
#include "Common.h"
#include "Terrain.h"
#include "Texture.h"

class CameraComponent;

class TerrainComponent : public Component
{
public:
	TerrainComponent();
	virtual ~TerrainComponent();

	void Initialize() override;
	void Terminate() override;
	void Render() override;

	void SetTerrain(std::string fileName, u32 width, u32 length, f32 maxHeight)
	{
		mFilename = fileName;
		mWidth = width;
		mLength = length;
		mMaxHeight = maxHeight;
	}
	void SetLayer(std::wstring texturename, u32 layer, f32 minHeight, f32 frequency)
	{
		mTextureFilename = texturename;
		mLayer = layer;
		mFrequency = frequency;
		mMinHeight = minHeight;
	}

private:
	Terrain mTerrain;
	Texture mTexture;
	Texture mTexture2;

	std::string mFilename;
	std::wstring mTextureFilename;
	u32 mWidth;
	u32 mLength;
	u32 mLayer;
	f32 mMaxHeight;
	f32 mMinHeight;
	f32 mFrequency;
};

#endif // !INCLUDED_ENGINE_TERRAINCOMPONENT_H