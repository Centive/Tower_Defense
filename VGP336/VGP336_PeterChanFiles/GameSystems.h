#ifndef INCLUDED_ENGINE_GAMESYSTEMS_H
#define INCLUDED_ENGINE_GAMESYSTEMS_H

class GraphicsSystem;
class InputSystem;

namespace GameSystems
{

void Register(GraphicsSystem& gs,
			  InputSystem& is);
void Unregister();

GraphicsSystem& GetGraphicsSystem();
InputSystem& GetInputSystem();

}

#endif // #ifndef INCLUDED_ENGINE_GAMESYSTEMS_H