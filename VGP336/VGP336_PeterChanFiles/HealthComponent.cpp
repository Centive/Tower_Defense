#include "Precompiled.h"

#include "HealthComponent.h"

#include "GameObject.h"
#include "World.h"

HealthComponent::HealthComponent()
	: Component("HealthComponent")
	, mCurrentHealth(0.0f)
	, mMaxHealth(0.0f)
{
}

HealthComponent::~HealthComponent()
{
}

void HealthComponent::Initialize()
{
	mCurrentHealth = mMaxHealth;
}
	
void HealthComponent::TakeDamage(f32 damage)
{
	if (!IsDead())
	{
		mCurrentHealth -= damage;
		if (IsDead())
		{
			World& world = GetObj().GetWorld();
			world.Destroy(GetObj().GetHandle());
		}
	}
}