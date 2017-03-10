#ifndef INCLUDED_ENGINE_SPAWNERCOMPONENT_H
#define INCLUDED_ENGINE_SPAWNERCOMPONENT_H


#include "Component.h"

class TransformComponent;

class SpawnerComponent : public Component
{
public:
	SpawnerComponent();
	virtual ~SpawnerComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

	void SetTemplatename(const char* templateName) { mTemplateName = templateName; }
	void SetObjectname(const char* objectName) { mObjectName = objectName; }
	void SetCooldown(f32 cooldown) { mCooldown = cooldown; }
	void SetUnitSpeed(const float speed) { mUnitSpeed = speed; }

private:
	TransformComponent* mTransformComponent;

	std::string mTemplateName;
	std::string mObjectName;

	f32 mCooldown;
	f32 mWaitTime;
	float mUnitSpeed;
};

#endif // !INCLUDED_ENGINE_SPAWNERCOMPONENT_H