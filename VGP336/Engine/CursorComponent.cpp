#include "Precompiled.h"

#include "World.h"
#include "CursorComponent.h"
#include "GameObject.h"
#include "GameSystems.h"
#include "InputSystem.h"
#include "InputTypes.h"
#include "SpriteComponent.h"
#include "TransformComponent.h"

CursorComponent::CursorComponent()
	: Component("CursorComponent")
{
}

CursorComponent::~CursorComponent()
{
}

void CursorComponent::Initialize()
{
	GetObj().GetComponent(mSpriteComponent, "SpriteComponent");
}

void CursorComponent::Update(f32 deltaTime)
{
	InputSystem& is = GameSystems::GetInputSystem();

	f32 screenX = (f32)is.GetMouseMoveX();
	f32 screenY = (f32)is.GetMouseMoveY();
	
	mSpriteComponent->UpdatePosition(Math::Vector2(screenX, screenY));

	if (is.IsMouseDown(Mouse::LBUTTON))
	{
		World& world = GetObj().GetWorld();
		GameObjectHandle handle = world.Create("../Data/Levels/Level1_objs/ducky_Model.xml", "Ducky");
		TransformComponent* transformComponent = nullptr;
		if (handle.Get()->FindComponent(transformComponent, "TransformComponent"));
		{
			transformComponent->SetPosition(Math::Vector3(screenX, 0, screenY));
		}
	}
}