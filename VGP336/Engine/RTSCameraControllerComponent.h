#ifndef INCLUDED_ENGINE_RTSCAMERACONTROLLERCOMPONENT_H
#define INCLUDED_ENGINE_RTSCAMERACONTROLLERCOMPONENT_H

#include "Component.h"

class CameraComponent;

class RTSCameraControllerComponent : public Component
{
public:
	RTSCameraControllerComponent();
	virtual ~RTSCameraControllerComponent();

	virtual void Initialize() override;
	virtual void Update(f32 deltaTime);

private:
	enum ESpeedState
	{
		Speed1,
		Speed2,
		Speed3
	};

	CameraComponent* mCameraComponent;

	ESpeedState curSpeed;
	float kCameraSpeed;
};

#endif // !INCLUDED_ENGINE_RTSCAMERACONTROLLERCOMPONENT_H