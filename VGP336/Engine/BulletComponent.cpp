#include "Precompiled.h"

#include "BulletComponent.h"

#include "GameObject.h"
#include "World.h"
#include "GameSystems.h"

//Components
#include "TransformComponent.h"
#include "ModelComponent.h"
#include "ColliderComponent.h"
#include "HealthComponent.h"

namespace
{
	bool HasArrived(const Math::Vector3& position, const Math::Vector3& destination, float arrivalDistance)
	{
		//Compute distance to destination
		const float distSqr = Math::DistanceXZSqr(position, destination);

		//Check arrival distance
		return (distSqr <= Math::Sqr(arrivalDistance));
	}
}

BulletComponent::BulletComponent()
	: Component("BulletComponent")
	, mTransformComponent(nullptr)
	, mModelComponent(nullptr)
	, mColliderComponent(nullptr)
	, mTarget(nullptr)
{
}

BulletComponent::~BulletComponent()
{
}

void BulletComponent::Initialize()
{
	GetObj().GetComponent(mTransformComponent, "TransformComponent");
	GetObj().GetComponent(mModelComponent, "ModelComponent");
	GetObj().GetComponent(mColliderComponent, "ColliderComponent");
}

void BulletComponent::Update(f32 deltaTime)
{
	World& world = GetObj().GetWorld();
	
	//if there is no target was not set then do nothing
	if (!mTarget) { return; }

	//Check if already dead
	HealthComponent* targetHealth = nullptr;
	if (mTarget->FindComponent(targetHealth, "HealthComponent") && !targetHealth->IsDead())
	{
		//Move the bullet
		Math::Vector3 destination;
		//Get Desitination of target
		TransformComponent* transformComponent = nullptr;
		if (mTarget->FindComponent(transformComponent, "TransformComponent"))
		{
			destination = transformComponent->GetPosition();
		}
		Math::Vector3 position = mTransformComponent->GetPosition();

		//Compute velocity and move
		{
			const float kMoveSpeed = 10.0f;
			Math::Vector3 direction = destination - position;
			Math::Vector3 velocity = Math::Normalize(direction) * kMoveSpeed;
			mTransformComponent->SetPosition(position + (velocity * deltaTime));
		}

		//Check for arrival
		{
			const float kArrivalDistance = 1.0f;
			if (HasArrived(position, destination, kArrivalDistance))
			{
				//Destroy bullet
				world.Destroy(GetObj().GetHandle());

				//Decrease enemy health
				HealthComponent* healthComponent = nullptr;
				if (mTarget->FindComponent(healthComponent, "HealthComponent"));
				{
					healthComponent->TakeDamage(1);
				}
				//isHit = true;
				return;
			}
		}
		return;
	}

	//Kill if target is gone
	world.Destroy(GetObj().GetHandle());
}