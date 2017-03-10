#ifndef INCLUDED_ENGINE_CAMERACONTROLLERCOMPONENT_H
#define INCLUDED_ENGINE_CAMERACONTROLLERCOMPONENT_H

#include "Component.h"

class CameraComponent;

class CameraControllerComponent : public Component
{
public:
	CameraControllerComponent();
	virtual ~CameraControllerComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:
	enum ESpeedState
	{
		Speed1,
		Speed2,
		Speed3
	};

	CameraComponent* mCameraComponent;

	ESpeedState curSpeed;
	f32 kMoveSpeed;
};

#endif // !INCLUDED_ENGINE_CAMERACONTROLLERCOMPONENT_H