#include "Precompiled.h"

#include "SpawnerComponent.h"

#include "GameObject.h"
#include "GameSystems.h"
#include "TransformComponent.h"
#include "AIComponent.h"
#include "World.h"

SpawnerComponent::SpawnerComponent()
	: Component("SpawnerComponent")
	, mTransformComponent(nullptr)
	, mCooldown(0.0f)
	, mWaitTime(0.0f)
	, mUnitSpeed(5.0f)
{
}

SpawnerComponent::~SpawnerComponent()
{
}

void SpawnerComponent::Initialize()
{
	GetObj().GetComponent(mTransformComponent, "TransformComponent");
	mTransformComponent->SetSnapToTerrain(true);
	mWaitTime = mCooldown;
}

void SpawnerComponent::Update(f32 deltaTime)
{
	//Update wait time
	mWaitTime -= deltaTime;
	if (mWaitTime <= 0.0f)
	{
		//It's time to spawn 
		World& world = GetObj().GetWorld();
		GameObjectHandle handle = world.Create(mTemplateName.c_str(), mObjectName.c_str());
	
		//If gameobject has transform, set its position to be the same as the spawner
		TransformComponent* transformComponent = nullptr;
		AIComponent* unit = nullptr;
		if (handle.Get()->FindComponent(transformComponent, "TransformComponent") && handle.Get()->FindComponent(unit, "AIComponent"));
		{
			transformComponent->SetPosition(mTransformComponent->GetPosition());
			unit->SetSpeed(mUnitSpeed);
		}
	
		//Reset wait time
		mWaitTime = mCooldown;
	}
}
