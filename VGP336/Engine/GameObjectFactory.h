#ifndef INCLUDED_ENGINE_GAMEOBJECTFACTORY_H
#define INCLUDED_ENGINE_GAMEOBJECTFACTORY_H

#include "GameObject.h"
#include "Utils.h"
#include <string>

class GameObjectFactory
{
public:
	GameObjectFactory(u16 capacity);

	GameObjectHandle Create(const char* templateFilename);
	void Destory(GameObjectHandle handle);

private:
	GameObjectAllocator mGameObjectAllocator;
};

#endif // !INCLUDED_ENGINE_GAMEOBJECTFACTORY_H