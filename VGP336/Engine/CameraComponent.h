#ifndef INCLUDED_ENGINE_CAMERACOMPONENT_H
#define INCLUDED_ENGINE_CAMERACOMPONENT_H


#include "Component.h"
#include "Camera.h"

class CameraComponent : public Component
{
public:
	CameraComponent();
	virtual ~CameraComponent();

	void Initialize() override;
	void Terminate() override;

	//setup camera
	void Setup(f32 fov, f32 aspectRatio, f32 nearPlane, f32 farPlane) { mCamera.Setup(fov, aspectRatio, nearPlane, farPlane); }
	void SetPosition(const Math::Vector3& position) { mCamera.SetPosition(position); }
	void SetDirection(const Math::Vector3& direction) { mCamera.SetDirection(direction); }
	void SetLookAt(const Math::Vector3& target) { mCamera.SetLookAt(target); }
	void SetFOV(f32 fov) { mCamera.SetFOV(fov); }

	//make it a main or not
	Camera& GetCamera() { return mCamera; }

private:
	Camera mCamera;
};

#endif // !INCLUDED_ENGINE_CAMERACOMPONENT_H