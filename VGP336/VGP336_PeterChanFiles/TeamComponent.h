#ifndef INCLUDED_ENGINE_TEAMCOMPONENT_H
#define INCLUDED_ENGINE_TEAMCOMPONENT_H

#include "Component.h"

class TeamComponent : public Component
{
public:
	TeamComponent();
	virtual ~TeamComponent();
	
	void SetTeamId(u32 teamId)	{ mTeamId = teamId; }
	u32 GetTeamId() const		{ return mTeamId; }
	
private:
	u32 mTeamId;
};

#endif // #ifndef INCLUDED_ENGINE_TEAMCOMPONENT_H