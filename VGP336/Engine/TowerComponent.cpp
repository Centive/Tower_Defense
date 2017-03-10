#include "Precompiled.h"

#include "TowerComponent.h"

#include "GameObject.h"
#include "World.h"

//Components
#include "TeamComponent.h"
#include "TransformComponent.h"
#include "HealthComponent.h"
#include "ColliderComponent.h"
#include "BulletComponent.h"
#include "ModelComponent.h"

namespace
{
	struct ClosestTargetVisitor : public WorldVisitor
	{
		Math::Vector3 position;
		GameObject* target;
		f32 closestDistanceSqr;
		u32 teamId;
		ClosestTargetVisitor(Math::Vector3 position, u32 teamId)
			: position(position)
			, target(nullptr)
			, closestDistanceSqr(600.0f)
			, teamId(teamId)
		{}

		virtual void operator()(GameObject* gameObject) override
		{
			const TransformComponent* transformComponent = nullptr;//(const TransformComponent*)gameObject->FindComponent("TransformComponent");
			if (!gameObject->FindComponent(transformComponent, "TransformComponent"))
			{
				return;
			}

			const TeamComponent* teamComponent = nullptr;//(const TeamComponent*)gameObject->FindComponent("TeamComponent");
			if (!gameObject->FindComponent(teamComponent, "TeamComponent") 
				|| teamComponent->GetTeamId() == teamId)		//if (teamComponent == nullptr ||																									//	teamComponent->GetTeamId() == teamId)
			{
				return;
			}

			const HealthComponent* healthComponent = nullptr;//(const HealthComponent*)gameObject->FindComponent("HealthComponent");
																											//if (healthComponent == nullptr ||
			if (!gameObject->FindComponent(healthComponent, "HealthComponent") 
				|| healthComponent->IsDead())	//	healthComponent->IsDead())
			{
				return;
			}

			const f32 distanceSqr = Math::DistanceXZSqr(position, transformComponent->GetPosition());
			if (distanceSqr < closestDistanceSqr)
			{
				closestDistanceSqr = distanceSqr;
				target = gameObject;
			}
		}
	};
}

TowerComponent::TowerComponent()
	: Component("TowerComponent")
	, mTeamComponent(nullptr)
	, mTransformComponent(nullptr)
	, mFireRate(1.0f)
	, mNextFire(0.0f)
{
}

TowerComponent::~TowerComponent()
{
}

void TowerComponent::Initialize()
{
	//Get all components it requires
	GetObj().GetComponent(mTeamComponent, "TeamComponent");
	GetObj().GetComponent(mTransformComponent, "TransformComponent");
	GetObj().GetComponent(mHealthComponent, "HealthComponent");
	GetObj().GetComponent(mColliderComponent, "ColliderComponent");
	GetObj().GetComponent(mModelComponent, "ModelComponent");
	
	//Snaps the transform's y to the terrain
	mTransformComponent->SetSnapToTerrain(true);
}

void TowerComponent::Update(f32 deltaTime)
{
	World& world = GetObj().GetWorld();
	Math::Vector3 pos = mTransformComponent->GetPosition();
	u32 teamId = mTeamComponent->GetTeamId();
	
	ClosestTargetVisitor visitor(pos, teamId);
	world.Visit(visitor);
	

	mNextFire -= deltaTime;
	//It's time to spawn 
	if (mNextFire < 0.0f)
	{
		if (visitor.target)
		{
			mNextFire = mFireRate;
			World& world = GetObj().GetWorld();
			GameObjectHandle handle = world.Create(mTemplateName.c_str(), "Projectile");
			BulletComponent* bulletComponent = nullptr;
			
			Math::Vector3 pos = mTransformComponent->GetPosition();
			u32 teamId = mTeamComponent->GetTeamId();
			
			ClosestTargetVisitor visitor(pos, teamId);
			world.Visit(visitor);
			
			TransformComponent* bulletTransform = nullptr;
			if (handle.Get()->FindComponent(bulletTransform, "TransformComponent"))
			{
				bulletTransform->SetPosition(mTransformComponent->GetPosition());
			}
			if (handle.Get()->FindComponent(bulletComponent, "BulletComponent"))
			{
				bulletComponent->SetTarget(visitor.target);
			}
		}
	}

//		//Reset next fire
//		mNextFire = mFireRate;
//
//		World& world = GetObj().GetWorld();
//
//		Math::Vector3 pos = mTransformComponent->GetPosition();
//		u32 teamId = mTeamComponent->GetTeamId();
//
//		ClosestTargetVisitor visitor(pos, teamId);
//		world.Visit(visitor);
//
//		//No team check yet
//		if (visitor.target != nullptr)
//		{
//			World& world = GetObj().GetWorld();
//			GameObjectHandle handle = world.Create(mTemplateName.c_str(), "Projectile");
//
//			//Find ai component
//			AIComponent* aiComponent = nullptr;
//			if (handle.Get()->FindComponent(aiComponent, "AIComponent"))
//			{
//				mBulletList.push_back(aiComponent);
//				//Get visitor's position
//				TransformComponent* targetTransformComponent = nullptr;
//				if (visitor.target->FindComponent(targetTransformComponent, "TransformComponent"));
//				{
//					//Set the projectile's position to the tower
//					targetTransformComponent->SetPosition(mTransformComponent->GetPosition());
//
//					mBulletTargets.push_back(targetTransformComponent);
//				}
//			}
//		}
//	}
//
//	if (!mBulletList.empty())
//	{
//		for (size_t i = 0; i != mBulletList.size() - 1; i++)
//		{
//			mBulletList[i]->SetDestination(mBulletTargets[i]->GetPosition());
//		}
//	}
}