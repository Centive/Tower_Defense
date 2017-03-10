#include "Precompiled.h"

#include "AIComponent.h"

#include "GameObject.h"
#include "World.h"
#include "GameSystems.h"

//Components
#include "TransformComponent.h"
#include "BulletComponent.h"
#include "ModelComponent.h"
#include "ColliderComponent.h"
#include "TeamComponent.h"
#include "HealthComponent.h"
#include "TeamComponent.h"


//Check if has arrived from destination
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
			, closestDistanceSqr(500.0f)
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

AIComponent::AIComponent()
	: Component("AIComponent")
	, mTransformComponent(nullptr)
	, mState(EState::Idle)
	, mDestination(Math::Vector3(50, 0, 50))
	, mMoveSpeed(5.0f)
	, mFireRate(1.0f)
	, mNextFire(0.0f)
{
}

AIComponent::~AIComponent()
{
}

void AIComponent::Initialize()
{
	GetObj().GetComponent(mTransformComponent,	"TransformComponent");
	GetObj().GetComponent(mModelComponent,		"ModelComponent");
	GetObj().GetComponent(mColliderComponent,	"ColliderComponent");
	GetObj().GetComponent(mHealthComponent,		"HealthComponent");
	GetObj().GetComponent(mTeamComponent,		"TeamComponent");
	mTransformComponent->SetSnapToTerrain(true);

	
}

void AIComponent::Update(f32 deltaTime)
{
	switch (mState)
	{
		case EState::Idle:
		{
			UpdateIdle(deltaTime);
			break;
		}
		case EState::Move:
		{
			UpdateMove(deltaTime);
			break;
		}
		case EState::Attack:
		{
			UpdateAttack(deltaTime);
			break;
		}
	}
}

void AIComponent::UpdateIdle(f32 deltaTime)
{
	Math::Vector3 position = mTransformComponent->GetPosition();

	//Check arrival
	const float kArrivalDistance = 1.0f;

	if (!HasArrived(position, mDestination, kArrivalDistance))
	{
		mState = EState::Move;
		return;
	}
}

void AIComponent::UpdateMove(f32 deltaTime)
{

	World& world = GetObj().GetWorld();
	u32 teamId = mTeamComponent->GetTeamId();


	//Compute distance to destination
	Math::Vector3 position = mTransformComponent->GetPosition();

	ClosestTargetVisitor visitor(position, teamId);
	world.Visit(visitor);

	//Check arrival distance
	const float kArrivalDistance = 1.0f;
	if (HasArrived(position, mDestination, kArrivalDistance))
	{
		mState = EState::Idle;
		return;
	}
	else if (visitor.target)
	{
		//attack if obj near me is a tower
		std::string n = visitor.target->GetName();
		if(n == "Ducky_Tower" || n == "Tower")
			mState = EState::Attack;
	}

	//Compute velocity and move
	Math::Vector3 direction = mDestination - position;
	Math::Vector3 velocity = Math::Normalize(direction) * mMoveSpeed;
	mTransformComponent->SetPosition(position + (velocity * deltaTime));

}

void AIComponent::UpdateAttack(f32 deltaTime)
{
	World& world = GetObj().GetWorld();
	u32 teamId = mTeamComponent->GetTeamId();

	//Compute distance to destination
	Math::Vector3 position = mTransformComponent->GetPosition();

	ClosestTargetVisitor visitor(position, teamId);
	world.Visit(visitor);
	mNextFire -= deltaTime;

	//FIRE THE DUCKS
	if (mNextFire < 0.0f)
	{
		if (visitor.target)
		{
			mNextFire = mFireRate;
			World& world = GetObj().GetWorld();
			GameObjectHandle handle = world.Create("../Data/Levels/Level1_objs/Enemy_Bullet.xml", "Projectile");

			Math::Vector3 pos = mTransformComponent->GetPosition();
			u32 teamId = mTeamComponent->GetTeamId();

			ClosestTargetVisitor visitor(pos, teamId);
			world.Visit(visitor);

			TransformComponent* bulletTransform = nullptr;
			if (handle.Get()->FindComponent(bulletTransform, "TransformComponent"))
			{
				bulletTransform->SetPosition(mTransformComponent->GetPosition());
			}

			BulletComponent* bulletComponent = nullptr;
			if (handle.Get()->FindComponent(bulletComponent, "BulletComponent"))
			{
				bulletComponent->SetTarget(visitor.target);
			}
		}
		else
		{
			mState = EState::Idle;
		}
	}
}