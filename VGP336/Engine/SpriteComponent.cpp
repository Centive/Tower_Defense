#include "Precompiled.h"
#include "SpriteComponent.h"
#include "GameObject.h"
#include "GameSystems.h"
#include "SpriteRenderer.h"
#include "World.h"


SpriteComponent::SpriteComponent()
	: Component("SpriteComponent")
{
}

SpriteComponent::~SpriteComponent()
{
}

void SpriteComponent::Initialize()
{
	GraphicsSystem& gs = GameSystems::GetGraphicsSystem();
	mSpriteRenderer.Initialize(gs);
	mTexture.Initialize(gs, L"../Data/Images/sword.png");
}

void SpriteComponent::Terminate()
{
	mTexture.Terminate();
	mSpriteRenderer.Terminate();
}

void SpriteComponent::Render2D()
{
	mSpriteRenderer.BeginRender();
	mSpriteRenderer.Draw(mTexture, mPosition);
	mSpriteRenderer.EndRender();
}