#ifndef INCLUDED_ENGINE_WORLD_H
#define INCLUDED_ENGINE_WORLD_H

#include "GameObjectFactory.h"

class Camera;
class Terrain;
class TransformComponent;
class SpriteRenderer;

//Functor - Function Object
// A class with a public virtual operator() declaration

struct WorldVisitor
{
	virtual void operator()(GameObject* gameObject) = 0;
};

class World
{
public:
	World(u32 capacity);
	~World();

	void Initialize();
	void Terminate();

	void LoadLevel(const char* levelFilename);

	GameObjectHandle Create(const char* templateFilename, const char* name);
	GameObjectHandle Find(const char* name);

	void Destroy(GameObjectHandle handle);

	void Visit(WorldVisitor& visitor);

	void Update(f32 deltaTime);
	void Render();
	void Render2D();

	void SetMainCamera(Camera* camera) { mCamera = camera; }
	Camera* GetMainCamera() { return mCamera; }

	void SetMainTerrain(Terrain* Terrain) { mTerrain = Terrain; }
	Terrain* GetMainTerrain() { return mTerrain; }

private:
	void DestroyInternal(GameObjectHandle handle);
	void PurgeDestroyList();

	typedef std::vector<GameObject*> GameObjectList;
	typedef std::vector<GameObjectHandle> DestroyList;

	GameObjectFactory mGameObjectFactory;

	GameObjectList mUpdateList;
	DestroyList mDestroyList;

	bool mUpdating;

	Camera* mCamera; //For temporary ownership
	Terrain* mTerrain;
};
#endif // !INCLUDED_ENGINE_WORLD_H