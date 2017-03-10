#ifndef INCLUDED_ENGINE_BULLETCOMPONENT_H
#define INCLUDED_ENGINE_BULLETCOMPONENT_H

#include "Component.h"
#include "EngineMath.h"

class TransformComponent;
class ModelComponent;
class ColliderComponent;

class BulletComponent : public Component
{
public:
	BulletComponent();
	virtual ~BulletComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

	void SetTarget(GameObject* obj) 
	{ 
		mTarget = obj; 
	}

private:
	TransformComponent* mTransformComponent;
	ModelComponent*		mModelComponent;
	ColliderComponent*	mColliderComponent;
	GameObject* mTarget;
};

#endif // !INCLUDED_ENGINE_BULLETCOMPONENT_H