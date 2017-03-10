#ifndef INCLUDED_ENGINE_MODELCOMPONENT_H
#define INCLUDED_ENGINE_MODELCOMPONENT_H

#include "Color.h"
#include "Component.h"
#include "EngineMath.h"

#include "MeshRenderer.h"
#include "Model.h"

class TransformComponent;
class CameraComponent;

class ModelComponent : public Component
{
public:
	ModelComponent();
	virtual ~ModelComponent();

	void Initialize() override;
	void Terminate() override;
	void Render() override;

	void SetModel(std::string fileName) { mFileName = fileName; }

private:
	TransformComponent* mTransformComponent;
	Model mModel;

	Math::Vector3 mPosition;
	std::string mFileName;
};

#endif // !INCLUDED_ENGINE_COLLIDERCOMPONENT_H