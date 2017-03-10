//====================================================================================================
// Filename:	SpriteRenderer.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "SpriteRenderer.h"

#include "GraphicsSystem.h"
#include "Texture.h"
#include <CommonStates.h>
#include <SpriteBatch.h>

//====================================================================================================
// Class Definitions
//====================================================================================================

SpriteRenderer::SpriteRenderer()
	: mpGraphicsSystem(nullptr)
	, mpStateObjects(nullptr)
	, mpSpriteBatch(nullptr)
{
	// Empty
}

//----------------------------------------------------------------------------------------------------

SpriteRenderer::~SpriteRenderer()
{
	ASSERT(mpSpriteBatch == nullptr, "[SpriteRenderer] Renderer not freed.");
}

//----------------------------------------------------------------------------------------------------

void SpriteRenderer::Initialize(GraphicsSystem& gs)
{
	ASSERT(mpSpriteBatch == nullptr, "[SpriteRenderer] Already initialized.");
	mpGraphicsSystem = &gs;
	mpStateObjects = new CommonStates(gs.GetDevice());
	mpSpriteBatch = new SpriteBatch(gs.GetContext());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Terminate()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Already terminated.");
	SafeDelete(mpSpriteBatch);
	SafeDelete(mpStateObjects);
	mpGraphicsSystem = nullptr;
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::BeginRender()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->Begin(SpriteSortMode_Deferred, mpStateObjects->NonPremultiplied());
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::EndRender()
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->End();
	
	// Restore state objects
	auto blendState = mpStateObjects->Opaque();
	auto depthStencilState = mpStateObjects->DepthDefault();
	auto rasterizerState = mpStateObjects->CullCounterClockwise();

	ID3D11DeviceContext* context = mpGraphicsSystem->GetContext();
	context->OMSetBlendState(blendState, nullptr, 0xFFFFFFFF);
	context->OMSetDepthStencilState(depthStencilState, 0);
	context->RSSetState(rasterizerState);
}

//----------------------------------------------------------------------------------------------------
void SpriteRenderer::Draw(Texture& texture, const Math::Vector2& position)
{
	ASSERT(mpSpriteBatch != nullptr, "[SpriteRenderer] Not initialized.");
	mpSpriteBatch->Draw(texture.mpTexture, DirectX::XMFLOAT2(position.x, position.y));
}
