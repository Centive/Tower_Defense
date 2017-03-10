#ifndef INCLUDED_ENGINE_AICOMPONENT_H
#define INCLUDED_ENGINE_AICOMPONENT_H

#include "Component.h"
#include "EngineMath.h"

//Requires these classes
class TransformComponent;
class ModelComponent;
class ColliderComponent;
class HealthComponent;
class TeamComponent;

class AIComponent : public Component
{
public:
	AIComponent();
	virtual ~AIComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

	void SetDestination(Math::Vector3 destination) { mDestination = destination; }
	void SetSpeed(float speed) { mMoveSpeed = speed; }

private:

	enum class EState
	{
		Idle,
		Move,
		Attack
	};

	void UpdateIdle(f32 deltaTime);
	void UpdateMove(f32 deltaTime);
	void UpdateAttack(f32 deltaTime);

	TransformComponent* mTransformComponent;
	ModelComponent* mModelComponent;
	ColliderComponent* mColliderComponent;
	HealthComponent* mHealthComponent;
	TeamComponent* mTeamComponent;

	EState mState;
	Math::Vector3 mDestination;
	float mMoveSpeed;

	f32 mFireRate;
	f32 mNextFire;
};

#endif // !INCLUDED_ENGINE_AICOMPONENT_H