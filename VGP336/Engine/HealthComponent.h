#ifndef INCLUDED_ENGINE_HEALTHCOMPONENT_H
#define INCLUDED_ENGINE_HEALTHCOMPONENT_H

#include "Component.h"
#include "EngineMath.h"
#include "Common.h"

class TransformComponent;
class TeamComponent;

class HealthComponent : public Component
{
public:
	HealthComponent();
	virtual ~HealthComponent();
	
	void Initialize() override;
	
	void TakeDamage(f32 damage);

	void SetMaxHealth(f32 maxHealth)	{ mMaxHealth = maxHealth; }
	bool IsDead() const;

private:
	const TeamComponent* mTeamComponent;
	TransformComponent* mTransformComponent;
	f32 mCurrentHealth;
	f32 mMaxHealth;
};

#endif // #ifndef INCLUDED_ENGINE_HEALTHCOMPONENT_H