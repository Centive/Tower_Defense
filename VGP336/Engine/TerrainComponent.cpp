#include "Precompiled.h"
#include "GameObject.h"
#include "GameSystems.h"
#include "TerrainComponent.h"
#include "World.h"

#include "Camera.h"
#include "CameraComponent.h"

TerrainComponent::TerrainComponent()
	: Component("TerrainComponent")
{
}

TerrainComponent::~TerrainComponent()
{
}

void TerrainComponent::Initialize()
{
	if (GetObj().GetWorld().GetMainTerrain() == nullptr)
	{
		GetObj().GetWorld().SetMainTerrain(&mTerrain);
	}
	GraphicsSystem& gs = GameSystems::GetGraphicsSystem();

	mTexture.Initialize(gs, mTextureFilename.c_str());
	mTerrain.Initialize(gs, mFilename.c_str(), mWidth, mLength, mMaxHeight);
	mTerrain.SetCamera(*GetObj().GetWorld().GetMainCamera());
	mTerrain.SetLayer(&mTexture, mLayer, mMinHeight, 5, mFrequency);


	
	mTexture2.Initialize(gs, L"../Data/Images/rock.jpg");
	mTerrain.SetLayer(&mTexture2, 1, 5, mMaxHeight, 20);
}

void TerrainComponent::Terminate()
{
	if (GetObj().GetWorld().GetMainTerrain() == &mTerrain)
	{
		GetObj().GetWorld().SetMainTerrain(nullptr);
	}
	mTerrain.Terminate();
	mTexture.Terminate();
	mTexture2.Terminate();
}

void TerrainComponent::Render()
{
	mTerrain.Render();
}