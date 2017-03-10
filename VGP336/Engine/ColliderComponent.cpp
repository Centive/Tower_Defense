#include "Precompiled.h"

#include "ColliderComponent.h"

#include "GameObject.h"
#include "SimpleDraw.h"
#include "TransformComponent.h"

ColliderComponent::ColliderComponent()
	: Component("ColliderComponent")
	, mTransformComponent(nullptr)
	, mCenter(Math::Vector3::Zero())
	, mExtend(Math::Vector3::One())
	, mColor(Color::Green())
{
}


ColliderComponent::~ColliderComponent()
{
}

void ColliderComponent::Initialize()
{
	GetObj().GetComponent(mTransformComponent, "TransformComponent");
}

void ColliderComponent::Render()
{
	SimpleDraw::AddAABB(GetAABB(), mColor);
}

Math::AABB ColliderComponent::GetAABB() const
{
	Math::Vector3 pos = mTransformComponent->GetPosition();
	return Math::AABB(mCenter + pos, mExtend);
}
