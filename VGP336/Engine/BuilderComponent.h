#ifndef INCLUDED_ENGINE_BUILDERCOMPONENT_H
#define INCLUDED_ENGINE_BUILDERCOMPONENT_H

#include "Component.h"

class TransformComponent;
class BuilderComponent : public Component
{
public:
	BuilderComponent();
	virtual ~BuilderComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:
	enum ESpeedState
	{
		Speed1,
		Speed2,
		Speed3
	};

	TransformComponent* mTransformComponent;
	ESpeedState curSpeed;
	float kCameraSpeed;
};

#endif // !INCLUDED_ENGINE_BUILDERCOMPONENT_H