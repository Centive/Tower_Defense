#ifndef INCLUDED_ENGINE_GAMEOBJECT_H
#define INCLUDED_ENGINE_GAMEOBJECT_H

#include "Component.h"
#include "BlockAllocator.h"
#include "Utils.h"

class World;
class GameObject;

typedef Handle<GameObject> GameObjectHandle;
typedef BlockAllocator<GameObject> GameObjectAllocator;

class GameObject
{
public:
	GameObject();
	~GameObject();

	void Initialize();
	void Terminate();
	void Update(f32 deltaTime);
	void Render();
	void Render2D();

	void AddComponent(Component* component);
	void SetName(const char *name) { mName = name; }

	template<typename T>
	bool FindComponent(T*& component, const char* name);
	template<typename T>
	bool FindComponent(const T*& component, const char* name) const;
	template<typename T>
	bool GetComponent(T*& component, const char* name);
	template<typename T>
	bool GetComponent(const T*& component, const char* name) const;

	World& GetWorld() { return *mWorld; }
	const World& GetWorld() const { return *mWorld; }

	GameObjectHandle GetHandle() const { return mHandle; }
	const char* GetName() const { return mName.c_str(); }

private:
	friend class World;

	GameObjectHandle mHandle;
	std::string mName;
	World* mWorld;

	typedef std::vector<Component*> Components;
	Components mComponents;
};

//
template<typename T>
bool GameObject::FindComponent(const T *& component, const char * name) const
{
	for (auto c : mComponents)
	{
		if (Utils::AreEqual(c->Getname(), name))
		{
			component = static_cast<const T*>(c);
			return true;
		}
	}
	return false;
}

//
template<typename T>
bool GameObject::FindComponent(T*& component, const char* name)
{
	for (auto c : mComponents)
	{
		if (Utils::AreEqual(c->Getname(), name))
		{
			component = static_cast<T*>(c);
			return true;
		}
	}
	return false;
}

//
template<typename T>
bool GameObject::GetComponent(T *& component, const char * name)
{
	bool success = FindComponent(component, name);
	ASSERT(success, "[GameObject] Cannot find %s.", name);
	return false;
}

//
template<typename T>
bool GameObject::GetComponent(const T *& component, const char * name) const
{
	bool success = FindComponent(component, name);
	ASSERT(success, "[GameObject] Cannot find %s.", name);
	return false;
}

#endif // !INCLUDED_ENGINE_GAMEOBJECT_H