#ifndef INCLUDED_ENGINE_SPRITECOMPONENT_H
#define INCLUDED_ENGINE_SPRITECOMPONENT_H

#include "Component.h"
#include "EngineMath.h"
#include "Texture.h"

//
#include <string>

#include "SpriteRenderer.h"

class Texture;

class SpriteComponent : public Component
{
public:
	SpriteComponent();
	virtual ~SpriteComponent();

	void Initialize() override;
	void Terminate() override;
	void Render2D() override;

	void SetPosition(Math::Vector2 pos) { mPosition = pos; }
	void SetTextureName(const char* textureName) { mTextureName = textureName; }

	Math::Vector2& GetPosition() { return mPosition; }

	void UpdatePosition(Math::Vector2 dist) { mPosition += dist; }

private:
	Math::Vector2 mPosition;
	std::string mTextureName;
	SpriteRenderer mSpriteRenderer;
	Texture mTexture;
};

#endif // !INCLUDED_ENGINE_SPRITECOMPONENT_H