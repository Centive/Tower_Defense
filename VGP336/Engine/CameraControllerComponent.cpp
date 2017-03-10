#include "Precompiled.h"
#include "CameraControllerComponent.h"
#include "CameraComponent.h"
#include "GameSystems.h"
#include "GameObject.h"
#include "InputSystem.h"
#include "InputTypes.h"


CameraControllerComponent::CameraControllerComponent()
	: Component("CameraControllerComponent")
	, curSpeed(ESpeedState::Speed1)
{
}

CameraControllerComponent::~CameraControllerComponent()
{
}

void CameraControllerComponent::Initialize()
{
	GetObj().GetComponent(mCameraComponent, "CameraComponent");
}

void CameraControllerComponent::Update(f32 deltaTime)
{
	//
	Camera& camera = mCameraComponent->GetCamera();

	InputSystem& is = GameSystems::GetInputSystem();


	if (is.IsKeyPressed(Keys::ONE)) { curSpeed = ESpeedState::Speed1; }
	if (is.IsKeyPressed(Keys::TWO)) { curSpeed = ESpeedState::Speed2; }
	if (is.IsKeyPressed(Keys::THREE)) { curSpeed = ESpeedState::Speed3; }

	switch (curSpeed)
	{
		case ESpeedState::Speed1:
		{
			kMoveSpeed = 25.0f;
			break;
		}
		case ESpeedState::Speed2:
		{
			kMoveSpeed = 100.0f;
			break;
		}
		case ESpeedState::Speed3:
		{
			kMoveSpeed = 200.0f;
			break;
		}
	}

	const f32 kTurnSpeed = 90.0f;

	if (is.IsKeyDown(Keys::W))
	{
		camera.Walk(kMoveSpeed * deltaTime);
	}
	if (is.IsKeyDown(Keys::S))
	{
		camera.Walk(-kMoveSpeed * deltaTime);
	}
	if (is.IsKeyDown(Keys::D))
	{
		camera.Strafe(kMoveSpeed * deltaTime);
	}
	if (is.IsKeyDown(Keys::A))
	{
		camera.Strafe(-kMoveSpeed * deltaTime);
	}
	if (is.IsKeyDown(Keys::SPACE))
	{
		camera.Rise(kMoveSpeed * deltaTime);
	}
	if (is.IsKeyDown(Keys::LSHIFT))
	{
		camera.Rise(-kMoveSpeed * deltaTime);
	}
	camera.Yaw(is.GetMouseMoveX() * kTurnSpeed * deltaTime);
	camera.Pitch(is.GetMouseMoveY() * kTurnSpeed * deltaTime);
}