#ifndef INCLUDED_ENGINE_PLAYERCOMPONENT_H
#define INCLUDED_ENGINE_PLAYERCOMPONENT_H

#include "Component.h"

class FSMComponent;
class TeamComponent;

class PlayerComponent : public Component
{
public:
	PlayerComponent();
	virtual ~PlayerComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:
	const TeamComponent* mTeamComponent;
	FSMComponent* mFSMComponent;
};

#endif // #ifndef INCLUDED_ENGINE_PLAYERCOMPONENT_H