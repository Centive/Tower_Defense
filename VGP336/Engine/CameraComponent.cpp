#include "Precompiled.h"
#include "CameraComponent.h"
#include "CameraControllerComponent.h"
#include "Camera.h"
#include "GameObject.h"
#include "World.h"

CameraComponent::CameraComponent()
	: Component("CameraComponent")
{
}

CameraComponent::~CameraComponent()
{
}

void CameraComponent::Initialize()
{
	if (GetObj().GetWorld().GetMainCamera() == nullptr)
	{
		GetObj().GetWorld().SetMainCamera(&mCamera);
	}
}

void CameraComponent::Terminate()
{
	if (GetObj().GetWorld().GetMainCamera() == &mCamera)
	{
		GetObj().GetWorld().SetMainCamera(nullptr);
	}
}