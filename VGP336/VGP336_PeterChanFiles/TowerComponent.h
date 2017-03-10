#ifndef INCLUDED_ENGINE_TOWERCOMPONENT_H
#define INCLUDED_ENGINE_TOWERCOMPONENT_H

#include "Component.h"

class TeamComponent;
class TransformComponent;

class TowerComponent : public Component
{
public:
	TowerComponent();
	virtual ~TowerComponent();
	
	virtual void Initialize() override;
	virtual void Update(f32 deltaTime) override;
	
	void SetTemplateName(const char* templateName)	{ mTemplateName = templateName; }
	void SetFireRate(f32 fireRate)					{ mFireRate = fireRate; }
	
private:
	const TeamComponent* mTeamComponent;
	const TransformComponent* mTransformComponent;

	std::string mTemplateName;
	f32 mFireRate;
};

#endif // #ifndef INCLUDED_ENGINE_TOWERCOMPONENT_H