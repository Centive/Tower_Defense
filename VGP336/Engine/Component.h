#ifndef INCLUDED_ENGINE_COMPONENT_H
#define INCLUDED_ENGINE_COMPONENT_H

class GameObject;

class Component
{
	NONCOPYABLE(Component);
public:
	Component(const char* name);
	virtual ~Component();

	virtual void Initialize() {}
	virtual void Terminate() {}

	virtual void Update(f32 deltaTime) {}
	virtual void Render() {}
	virtual void Render2D() {}

	const char* Getname() const { return mName; }

	GameObject& GetObj() { return *mGameObject; }
	const GameObject& GetObj() const { return *mGameObject; }

private:
	friend class GameObject;
	const char* mName;
	GameObject* mGameObject;
};

#endif // !INCLUDED_ENGINE_COMPONENT_H