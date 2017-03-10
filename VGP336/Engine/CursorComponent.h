#ifndef INCLUDED_ENGINE_CURSORCOMPONENT_H
#define INCLUDED_ENGINE_CURSORCOMPONENT_H


#include "Component.h"

class SpriteComponent;

class CursorComponent : public Component
{
public:
	CursorComponent();
	virtual ~CursorComponent();

	void Initialize() override;
	void Update(f32 deltaTime) override;

private:
	SpriteComponent* mSpriteComponent;
};

#endif // !INCLUDED_ENGINE_CURSORCOMPONENT_H