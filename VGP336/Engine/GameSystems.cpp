#include "Precompiled.h"
#include "GameSystems.h"

namespace
{
	GraphicsSystem* sGraphicsSystem = nullptr;
	InputSystem* sInputSystem = nullptr;
	MeshRenderer* sMeshRenderer = nullptr;
	SpriteRenderer* sSpriteRender = nullptr;
}

void GameSystems::Register(GraphicsSystem& gs,
						   InputSystem& is,
							MeshRenderer& mr,
							SpriteRenderer& sr)
{
	sGraphicsSystem = &gs;
	sInputSystem = &is;
	sMeshRenderer = &mr;
	sSpriteRender = &sr;
}

void GameSystems::Unregister()
{
	sGraphicsSystem = nullptr;
	sInputSystem = nullptr;
	sMeshRenderer = nullptr;
	sSpriteRender = nullptr;
}

GraphicsSystem& GameSystems::GetGraphicsSystem()	{ return *sGraphicsSystem; }
InputSystem& GameSystems::GetInputSystem()			{ return *sInputSystem; }
MeshRenderer& GameSystems::GetMeshRenderer() { return *sMeshRenderer; }
SpriteRenderer& GameSystems::GetSpriteRenderer() { return *sSpriteRender; }
