#include "GameApp.h"
namespace
{
	const u16 kMaxGameObjectCount = 1000;
}

GameApp::GameApp():mWorld(kMaxGameObjectCount) {}

GameApp::~GameApp() {}

void GameApp::OnInitialize(u32 width, u32 height)
{
	//create our window and attach to our application
	mWindow.Initialize(GetInstance(), GetAppName(), width, height);
	HookWindow(mWindow.GetWindowHandle());

	//initialize our timer
	mTimer.Initialize();

	//initialize the graphics system
	mGraphicsSystem.Initialize(mWindow.GetWindowHandle(), false);
	//mSpriteRenderer.Initialize(mGraphicsSystem);
	SimpleDraw::Initialize(mGraphicsSystem, 999999);

	//initialize the input system
	mInputSystem.Initialize(mWindow.GetWindowHandle());
	mMeshRenderer.Initialize(mGraphicsSystem);
	mSpriteRenderer.Initialize(mGraphicsSystem);
	mFont.Initialize(mGraphicsSystem, L"../Data/Fonts/arial_16.font");
	//register sub-system
	GameSystems::Register(mGraphicsSystem, mInputSystem, mMeshRenderer, mSpriteRenderer);

	//Initialize level
	mWorld.Initialize();
	mWorld.LoadLevel("../Data/Levels/Level1.xml");
	mMeshRenderer.SetCamera(*mWorld.GetMainCamera());

	//mTexture.Initialize(mGraphicsSystem, L"../Data/Images/sword.png");

	//test
	//edit world
	//temp.... create a gameobject
	//mHandle[0] = mGameObjectFactory.Create("../Data/template/red_box.xml");
	//mHandle[1] = mGameObjectFactory.Create("../Data/template/blue_box.xml");
	//mHandle[2] = mGameObjectFactory.Create("../Data/template/green_box.xml");
	////add transform component
	//TransformComponent* transformComponent = new TransformComponent();
	//transformComponent->SetPosition(Math::Vector3(0.0f, 0.0f, 0.0f));
	//gameObject->AddComponent(transformComponent);
	//
	////add collider component
	//ColliderComponent* colliderComponent = new ColliderComponent();
	//colliderComponent->SetCenter(Math::Vector3(0.0f, 1.0f, 0.0f));
	//colliderComponent->SetExtend(Math::Vector3(0.5f, 1.0f, 0.5));
	//colliderComponent->SetColor(Color::Blue());
	//gameObject->AddComponent(colliderComponent);
	//gameObject->Initialize();
	//gameObject1->Initialize();
	//gameObject2->Initialize();
	//gameObject3->Initialize();
	//mGameObjectfactory.create("../Data/templates/red_box.xml");
	//mGameObjectfactory.create("../Data/templates/blue_box.xml");
	//mGameObjectfactory.create("../Data/templates/green_box.xml");
	//edit world
	//mTexture.Initialize(mGraphicsSystem, L"../Data/Images/rock.jpg");
	//
	//mTerrain.Initialize(mGraphicsSystem, "../Data/Heightmaps/heightmap.raw", 256, 256, 10);
	//mTerrain.SetCamera(*mWorld.GetMainCamera());
	//mTerrain.SetLayer(&mTexture, 0, 0, 10, 15);
	//mTerrain.SetLayer(&mTexture, 1, 0, 10, 15);
	//mTerrain.SetLayer(&mTexture, 2, 0, 10, 15);
	//mTerrain.SetLayer(&mTexture, 3, 0, 10, 15);
}

void GameApp::OnTerminate()
{	
	//edit world
	//temp.... terminate our gameobject 
	//GameObject* gameObject1 = mHandle[0].Get();
	//gameObject1->Terminate();
	//mGameObjectFactory.Destory(mHandle[0]);
	//
	//GameObject* gameObject2 = mHandle[1].Get();
	//gameObject2->Terminate();
	//mGameObjectFactory.Destory(mHandle[1]);
	//
	//GameObject* gameObject3 = mHandle[2].Get();
	//gameObject3->Terminate();
	//mGameObjectFactory.Destory(mHandle[2]);

	//mTexture.Terminate();


	//WORLD
	mWorld.Terminate();

	//terminate our sub-systems
	mInputSystem.Terminate();
	SimpleDraw::Terminate();
	mGraphicsSystem.Terminate();
	mMeshRenderer.Terminate();
	mFont.Terminate();
	mSpriteRenderer.Terminate();
	//detach our window and terminate it
	UnhookWindow();
	mWindow.Terminate();
}

void GameApp::OnUpdate()
{
	//handle message from the operating system
	if (mWindow.HandleMessage())
	{
		//we recieved a quit signal, just exit
		mRunning = false;
		return;
	}

	//listen for inputs and update
	mInputSystem.Update(); 
	mTimer.Update();

	//check input
	if (mInputSystem.IsKeyPressed(Keys::ESCAPE))
	{

		//if ESC is pressed, we are done
		PostQuitMessage(0);
		return;
	}
	else if (mInputSystem.IsKeyPressed(Keys::F1))
	{
		//toggle fullscree/window modes
		mGraphicsSystem.ToggleFullscreen();
	}
	//deltatime
	const f32 kDeltaTime = mTimer.GetElapsedTime();
	mWorld.Update(kDeltaTime);								//update world

	//BEGIN WORLD
	mGraphicsSystem.BeginRender(Color::Black());
	
	mWorld.Render();										//render world
	SimpleDraw::Render(*mWorld.GetMainCamera());			//render the world camera

	//update/reder
	mSpriteRenderer.BeginRender();							//Start rendering sprites
	mWorld.Render2D();										//render2d world
	mFont.Render(mSpriteRenderer, L"WASD to move Camera\nArrows Keys to move player truck\nSpace to place towers\nDO NOT LEFT CLICK SPAM", 5, 5);	//render font
	mSpriteRenderer.EndRender();							//End rendering sprites
	
	//END WORLD
	mGraphicsSystem.EndRender();
}