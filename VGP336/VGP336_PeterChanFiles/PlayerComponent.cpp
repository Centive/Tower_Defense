#include "Precompiled.h"

#include "PlayerComponent.h"

#include "Camera.h"
#include "ColliderComponent.h"
#include "FSMComponent.h"
#include "GameObject.h"
#include "GameSystems.h"
#include "GraphicsSystem.h"
#include "HealthComponent.h"
#include "InputSystem.h"
#include "InputTypes.h"
#include "TeamComponent.h"
#include "TransformComponent.h"
#include "Terrain.h"
#include "World.h"

namespace
{
	struct TargetVisitor : public WorldVisitor
	{
		Math::Ray ray;
		GameObject* target;
		f32 closestDistance;
		u32 teamId;

		TargetVisitor(Math::Ray ray, u32 teamId)
			: ray(ray)
			, target(nullptr)
			, closestDistance(FLT_MAX)
			, teamId(teamId)
		{}

		virtual void operator()(GameObject* gameObject) override
		{
			const TeamComponent* teamComponent = nullptr;
			if (gameObject->FindComponent(teamComponent) || teamComponent->GetTeamId() == teamId)
			{
				return;
			}

			const HealthComponent* healthComponent = nullptr;
			if (gameObject->FindComponent(healthComponent) || healthComponent->IsDead())
			{
				return;
			}

			const ColliderComponent* colliderComponent = nullptr;
			gameObject->GetComponent(colliderComponent);
			Math::AABB aabb = colliderComponent->GetAABB();

			f32 entryDistance, exitDistance;
			if (Math::Intersect(ray, aabb, entryDistance, exitDistance))
			{
				if (entryDistance < closestDistance)
				{
					closestDistance = entryDistance;
					target = gameObject;
				}
			}
		}
	};
}

PlayerComponent::PlayerComponent()
	: mTeamComponent(nullptr)
	, mFSMComponent(nullptr)
{
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Initialize()
{
	GetObj().GetComponent(mTeamComponent);
	GetObj().GetComponent(mFSMComponent);
}

void PlayerComponent::Update(f32 deltaTime)
{
	GraphicsSystem& gs = GameSystems::GetGraphicsSystem();
	InputSystem& is = GameSystems::GetInputSystem();

	World& world = GetObj().GetWorld();
	const Camera* camera = world.GetMainCamera();
	const Terrain* terrain = world.GetMainTerrain();
	if (camera != nullptr && terrain != nullptr)
	{
		if (is.IsMouseDown(Mouse::RBUTTON))
		{
			s32 screenX = is.GetMouseScreenX();
			s32 screenY = is.GetMouseScreenY();
			u32 screenWidth = gs.GetWidth();
			u32 screenHeight = gs.GetHeight();
			Math::Ray ray = camera->ScreenPointToRay(screenX, screenY, screenWidth, screenHeight);

			// Check if we have clicked on a target
			TargetVisitor visitor(ray, mTeamComponent->GetTeamId());
			world.Visit(visitor);
			if (visitor.target != nullptr)
			{
				mFSMComponent->SetTarget(visitor.target->GetHandle());
			}
			// Else check against the terrain
			else
			{
				f32 distance;
				if (terrain->Intersect(ray, distance))
				{
					Math::Vector3 position = ray.org + (ray.dir * distance);
					mFSMComponent->SetDestination(position);
				}
			}
		}
	}
}