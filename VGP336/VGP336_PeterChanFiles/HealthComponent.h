#ifndef INCLUDED_ENGINE_HEALTHCOMPONENT_H
#define INCLUDED_ENGINE_HEALTHCOMPONENT_H

#include "Component.h"

class HealthComponent : public Component
{
public:
	HealthComponent();
	virtual ~HealthComponent();

	virtual void Initialize() override;
	
	void TakeDamage(f32 damage);

	void SetMaxHealth(f32 maxHealth)	{ mMaxHealth = maxHealth; }
	bool IsDead() const					{ return mCurrentHealth <= 0.0f; }

private:
	f32 mCurrentHealth;
	f32 mMaxHealth;
};

#endif // #ifndef INCLUDED_ENGINE_HEALTHCOMPONENT_H