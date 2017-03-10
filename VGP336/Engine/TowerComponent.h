#ifndef INCLUDED_ENGINE_TOWERCOMPONENT_H
#define INCLUDED_ENGINE_TOWERCOMPONENT_H

#include "Component.h"
#include "EngineMath.h"
#include "Common.h"
#include <vector>

class TeamComponent;
class TransformComponent;
class HealthComponent;
class ColliderComponent;
class ModelComponent;

class TowerComponent : public Component
{
public:
	TowerComponent();
	virtual ~TowerComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;
	
	void SetTemplateName(const char* templateName)	{ mTemplateName = templateName; }
	void SetFireRate(f32 fireRate)					{ mFireRate = fireRate; }
	
private:
	const TeamComponent* mTeamComponent;
	TransformComponent* mTransformComponent;
	HealthComponent* mHealthComponent;
	ColliderComponent* mColliderComponent;
	ModelComponent* mModelComponent;

	std::string mTemplateName;
	f32 mFireRate;
	f32 mNextFire;
};

#endif // #ifndef INCLUDED_ENGINE_TOWERCOMPONENT_H