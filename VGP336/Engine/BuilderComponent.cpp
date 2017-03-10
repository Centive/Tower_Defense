#include "Precompiled.h"
#include "BuilderComponent.h"
#include "TransformComponent.h"
#include "GameObject.h"
#include "GameSystems.h"
#include "InputSystem.h"
#include "InputTypes.h"
#include "World.h"


BuilderComponent::BuilderComponent()
	: Component("BuilderComponent")
	, curSpeed(ESpeedState::Speed1)
	, mTransformComponent(nullptr)
{
}

BuilderComponent::~BuilderComponent()
{
}

void BuilderComponent::Initialize()
{
	GetObj().GetComponent(mTransformComponent, "TransformComponent");
	mTransformComponent->SetSnapToTerrain(true);
}

void BuilderComponent::Update(f32 deltaTime)
{	
	InputSystem& is = GameSystems::GetInputSystem();
	
	//Speed controls
	{
		//Change speed
		if (is.IsKeyPressed(Keys::ONE)) { curSpeed = ESpeedState::Speed1; }
		if (is.IsKeyPressed(Keys::TWO)) { curSpeed = ESpeedState::Speed2; }
		if (is.IsKeyPressed(Keys::THREE)) { curSpeed = ESpeedState::Speed3; }
		//Set Speed
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
	}

	//Move controls
	if (is.IsKeyDown(Keys::UP))
	{
		mTransformComponent->UpdatePosition(Math::Vector3(0,0,kCameraSpeed*deltaTime));
	}
	if (is.IsKeyDown(Keys::DOWN))
	{
		mTransformComponent->UpdatePosition(Math::Vector3(0, 0, -kCameraSpeed*deltaTime));
	}
	if (is.IsKeyDown(Keys::RIGHT)) 
	{
		mTransformComponent->UpdatePosition(Math::Vector3(kCameraSpeed*deltaTime, 0,0));
	}
	if (is.IsKeyDown(Keys::LEFT))
	{
		mTransformComponent->UpdatePosition(Math::Vector3(-kCameraSpeed*deltaTime, 0, 0));
	}
	
	//Spawn a tower
	if (is.IsKeyPressed(Keys::SPACE))
	{
		//spawn tower
		World& world = GetObj().GetWorld();
		GameObjectHandle handle = world.Create("../Data/Levels/Level1_objs/Tower1.xml", "Tower");

		//spawn tower to this obj's position
		TransformComponent* transformComponent = nullptr;
		if (handle.Get()->FindComponent(transformComponent, "TransformComponent"))
		{
			transformComponent->SetPosition(mTransformComponent->GetPosition());
			transformComponent->SetSnapToTerrain(true);
		}
	}
}