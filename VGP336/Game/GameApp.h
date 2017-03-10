#ifndef  INCLUDED_GAMEAPP_H
#define  INCLUDED_GAMEAPP_H

#include <Engine.h>

class GameApp : public Application
{
public:
	GameApp();
	virtual ~GameApp();
private:
	void OnInitialize(u32 width, u32 Heightmap) override;
	void OnTerminate() override;
	void OnUpdate()	override;

	Window mWindow;
	Timer mTimer;
	GraphicsSystem mGraphicsSystem;
	InputSystem mInputSystem;

	MeshRenderer mMeshRenderer;
	SpriteRenderer mSpriteRenderer;
	Texture mTexture;
	Model mModel;
	World mWorld;
	Font mFont;
	//for homework 4:49:00
	// - add camera component			(has a mCamera member)
	// - add cameraControllerComponent	(checks input and move camera)
	// - add camera.xml template which has these components in it ^^^^^^
	// - remove mCamera from gameApp
	// - add get/set methods to world for a camera pointer (e.g. SetMainCamera/GetMainCamera)
	// - cameraComponent::initialize should set the main camera if none is set in the world

	//We dont need this because world handles it
	//GameObjectFactory mGameObjectFactory;
	//GameObjectHandle *mHandle;//mHandle <- create three handles for 3 gameobjects
};
#endif // ! INCLUDED_GAMEAPP_H