#include "Precompiled.h"
#include "RTSCameraControllerComponent.h"
#include "CameraComponent.h"
#include "GameObject.h"
#include "GameSystems.h"
#include "InputSystem.h"
#include "InputTypes.h"


RTSCameraControllerComponent::RTSCameraControllerComponent()
	: Component("RTSCameraControllerComponent")
	, curSpeed(ESpeedState::Speed1)
{
}

RTSCameraControllerComponent::~RTSCameraControllerComponent()
{
}

void RTSCameraControllerComponent::Initialize()
{
	GetObj().GetComponent(mCameraComponent, "CameraComponent");
	mCameraComponent->GetCamera().SetPosition(Math::Vector3(7.0f, 75.0f, 0.0f));
	mCameraComponent->GetCamera().SetDirection(Math::Vector3(0.0f, -2.0f, 1.0f));

	//mCameraComponent->GetCamera().SetPosition();
	//FOR AN IMMERSIVE TOP DOWN RTS VIEW
	//7, 75, 0 set position of camera
	//0, -2, 1 and direction
}

void RTSCameraControllerComponent::Update(f32 deltaTime)
{	
	//
	Camera& camera = mCameraComponent->GetCamera();

	InputSystem& is = GameSystems::GetInputSystem();
	const float kZoomSpeed = 0.5f;

	if (is.IsKeyPressed(Keys::ONE)) { curSpeed = ESpeedState::Speed1; }
	if (is.IsKeyPressed(Keys::TWO)) { curSpeed = ESpeedState::Speed2; }
	if (is.IsKeyPressed(Keys::THREE)) { curSpeed = ESpeedState::Speed3; }

	switch (curSpeed)
	{
		case ESpeedState::Speed1:
		{
			kCameraSpeed = 50.0f;
			break;
		}
		case ESpeedState::Speed2:
		{
			kCameraSpeed = 100.0f;
			break;
		}
		case ESpeedState::Speed3:
		{
			kCameraSpeed = 200.0f;
			break;
		}
	}

	//Check Camera Component
	Math::Vector3 position = camera.GetPosition();

	if (is.IsKeyDown(Keys::W))
	{
		position.z += kCameraSpeed * deltaTime;
	}
	if (is.IsKeyDown(Keys::S))
	{
		position.z -= kCameraSpeed * deltaTime;
	}
	if (is.IsKeyDown(Keys::D)) 
	{
		position.x += kCameraSpeed * deltaTime;
	}
	if (is.IsKeyDown(Keys::A))
	{
		position.x -= kCameraSpeed * deltaTime;
	}
	camera.SetPosition(position);

	// check camera zoom
	f32 fov = camera.GetFOV();
	fov -= is.GetMouseMoveZ() * kZoomSpeed * deltaTime;
	camera.SetFOV(fov);
}