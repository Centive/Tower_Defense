#ifndef INCLUDED_ENGINE_COLLIDERCOMPONENT_H
#define INCLUDED_ENGINE_COLLIDERCOMPONENT_H

#include "Color.h"
#include "Component.h"
#include "EngineMath.h"

class TransformComponent;

class ColliderComponent : public Component
{
public:
	ColliderComponent();
	virtual ~ColliderComponent();

	void Initialize() override;
	void Render() override;

	void SetCenter(const Math::Vector3& center) { mCenter = center; }
	void SetExtend(const Math::Vector3& extend) { mExtend = extend; }
	void SetColor(const Color& color) { mColor = color; }

	Math::AABB GetAABB() const;

private:
	const TransformComponent* mTransformComponent;
	Math::Vector3 mCenter;
	Math::Vector3 mExtend;
	Color mColor;
};

#endif // !INCLUDED_ENGINE_COLLIDERCOMPONENT_H