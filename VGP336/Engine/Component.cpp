#include "Precompiled.h"
#include "Component.h"


Component::Component(const char* name)
	: mName(name)
	, mGameObject(nullptr)
{
}

Component::~Component()
{
}
