#include "Precompiled.h"

#include "TowerComponent.h"

#include "GameObject.h"
#include "HealthComponent.h"
#include "TeamComponent.h"
#include "TransformComponent.h"
#include "World.h"

namespace
{
	struct ClosetTargetVisitor : public WorldVisitor
	{
		Math::Vector3 position;
		GameObject* target;
		f32 closestDistanceSqr;
		u32 teamId;

		ClosetTargetVisitor(Math::Vector3 position, u32 teamId)
			: position(position)
			, target(nullptr)
			, closestDistanceSqr(FLT_MAX)
			, teamId(teamId)
		{}

		virtual void operator()(GameObject* gameObject) override
		{
			const TransformComponent* transformComponent = (const TransformComponent*)gameObject->FindComponent("TransformComponent");
			if (transformComponent == nullptr)
			{
				return;
			}

			const TeamComponent* teamComponent = (const TeamComponent*)gameObject->FindComponent("TeamComponent");
			if (teamComponent == nullptr ||
				teamComponent->GetTeamId() == teamId)
			{
				return;
			}

			const HealthComponent* healthComponent = (const HealthComponent*)gameObject->FindComponent("HealthComponent");
			if (healthComponent == nullptr ||
				healthComponent->IsDead())
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
{
}

TowerComponent::~TowerComponent()
{
}
	
void TowerComponent::Initialize()
{
	mTransformComponent = (TransformComponent*)GetObj().GetComponent("TransformComponent");
}

void TowerComponent::Update(f32 deltaTime)
{
	// TODO: Add a timer, so we don't fire constantly

	World& world = GetObj().GetWorld();
	
	Math::Vector3 pos = mTransformComponent->GetPosition();
	u32 teamId = mTeamComponent->GetTeamId();

	ClosetTargetVisitor visitor(pos, teamId);
	world.Visit(visitor);

	if (visitor.target != nullptr)
	{
		// Attack!
		// TODO:
		//	Spawn projectile using xml
		//	Set it's target in ProjectileComponent
		//	reset timer
	}
}