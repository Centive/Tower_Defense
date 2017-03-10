#include "Precompiled.h"

#include "ModelComponent.h"
#include <GameSystems.h>
#include "TransformComponent.h"
#include "GameObject.h"
#include "World.h"
#include "Camera.h"
#include "CameraComponent.h"

ModelComponent::ModelComponent()
	: Component("ModelComponent")
	, mPosition(0.0f, 0.0f, 0.0f)

{
}

ModelComponent::~ModelComponent()
{
}

void ModelComponent::Initialize()
{
	GetObj().GetComponent(mTransformComponent, "TransformComponent");
	mPosition = mTransformComponent->GetPosition();

	GraphicsSystem& gs = GameSystems::GetGraphicsSystem();

	mModel.Load(gs, mFileName.c_str());
}

void ModelComponent::Terminate()
{
	mModel.Unload();
}

void ModelComponent::Render()
{
	mModel.Render(GameSystems::GetMeshRenderer(), Math::Matrix::Translation(mTransformComponent->GetPosition()));
}