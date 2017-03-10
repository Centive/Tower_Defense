#include "Precompiled.h"
#include "GameSystems.h"

namespace
{
	GraphicsSystem* sGraphicsSystem = nullptr;
	InputSystem* sInputSystem = nullptr;
}

void GameSystems::Register(GraphicsSystem& gs,
						   InputSystem& is)
{
	sGraphicsSystem = &gs;
	sInputSystem = &is;
}

void GameSystems::Unregister()
{
	sGraphicsSystem = nullptr;
	sInputSystem = nullptr;
}

GraphicsSystem& GameSystems::GetGraphicsSystem()	{ return *sGraphicsSystem; }
InputSystem& GameSystems::GetInputSystem()			{ return *sInputSystem; }
