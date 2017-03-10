#ifndef INCLUDED_ENGINE_GAMESYSTEMS_H
#define INCLUDED_ENGINE_GAMESYSTEMS_H

class GraphicsSystem;
class InputSystem;
class MeshRenderer;
class SpriteRenderer;

namespace GameSystems
{

void Register(GraphicsSystem& gs,
				InputSystem& is,
				MeshRenderer& mr,
				SpriteRenderer& sr);

void Unregister();

GraphicsSystem& GetGraphicsSystem();
InputSystem& GetInputSystem();
MeshRenderer& GetMeshRenderer();
SpriteRenderer& GetSpriteRenderer();
}

#endif // #ifndef INCLUDED_ENGINE_GAMESYSTEMS_H