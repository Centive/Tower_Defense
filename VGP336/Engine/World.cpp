#include "Precompiled.h"
#include "World.h"

#include "GameObject.h"
#include "Utils.h"
#include "tinyxml.h"
#include "TransformComponent.h"

namespace
{
	TransformComponent* AddTransformComponent(TiXmlElement*& pElem)
	{
		TransformComponent* transformComponent = new TransformComponent();

		float pos[3];
		for (int i = 0; i < 3; pElem = pElem->NextSiblingElement(), i++)
		{
			pos[i] = strtof(pElem->GetText(), 0);
		}

		transformComponent->SetPosition(Math::Vector3(pos[0], pos[1], pos[2]));

		return transformComponent;
	}
}

World::World(u32 capacity)
	:mGameObjectFactory(capacity)
	, mUpdating(false)
	, mCamera(nullptr)
	, mTerrain(nullptr)
{
}

World::~World()
{
}

void World::Initialize()
{
}

void World::Terminate()
{
	ASSERT(!mUpdating, "[World] Cannot terminate world during update.");

	//Add all active objects to the destroy list
	for (auto gameobject : mUpdateList)
	{
		mDestroyList.push_back(gameobject->GetHandle());
	}
	mUpdateList.clear();

	//now destroy everything
	PurgeDestroyList();

}

void World::LoadLevel(const char * levelFilename)
{
	TiXmlDocument doc(levelFilename);

	ASSERT(doc.LoadFile(), "Cannot load level");

	TiXmlHandle hDoc(&doc);
	TiXmlElement* pElem;
	TiXmlHandle hRoot(0);

	pElem = hDoc.FirstChild().Element();

	ASSERT(pElem, "The xml file is empty");

	hRoot = TiXmlHandle(pElem);

	//does this xml really have gameobjects? 
	if ((std::string)pElem->Value() == "GameObjects")
	{
		//iterate through the game objects
		for (TiXmlElement* pTemp1 = TiXmlHandle(pElem).FirstChild().Element();
			pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//found a gameobject!
			if ((std::string)pTemp1->Value() == "GameObject")
			{
				TiXmlElement* pTemp2 = TiXmlHandle(pTemp1).FirstChild().Element();

				//Get the NAME of the gameobject and TEMPLATE
				const char* name = pTemp2->GetText();
				pTemp2 = pTemp2->NextSiblingElement();

				//Create the template gameobject
				Create(pTemp2->GetText(), name);

				//Check if the gameobject is given a transform component
				pTemp2 = pTemp2->NextSiblingElement();
				if (pTemp2)
				{
					std::string pName = pTemp2->Attribute("name");
					if (pName == "Position")
					{
						//goto through the coordinates in Position
						TiXmlElement* pTemp3 = TiXmlHandle(pTemp2).FirstChild().Element();

						float pos[3];//
						for (int i = 0; i < 3; pTemp3 = pTemp3->NextSiblingElement(), i++)
						{
							pos[i] = strtof(pTemp3->GetText(), 0);//add the position
						}

						//Add that component
						TransformComponent* transform = new TransformComponent();
						transform->SetPosition(Math::Vector3(pos[0], pos[1], pos[2]));
						mUpdateList.back()->AddComponent(transform);
					}
				}
			}
		}
	}
}

GameObjectHandle World::Create(const char * templateFilename, const char * name)
{
	GameObjectHandle handle = mGameObjectFactory.Create(templateFilename);
	ASSERT(handle.IsValid(), "[World] Failed to create game object with template %s", templateFilename);

	// initialize the game object
	GameObject* gameObject = handle.Get();
	gameObject->mWorld = this;
	gameObject->mHandle = handle;
	gameObject->mName = name;
	gameObject->Initialize();

	//add game objects to the update list
	mUpdateList.push_back(gameObject);

	return handle;
}

GameObjectHandle World::Find(const char * name)
{
	for (auto gameObject : mUpdateList)
	{
		if (Utils::AreEqual(gameObject->GetName(), name))
		{
			return gameObject->GetHandle();
		}
	}
	return GameObjectHandle();
}

void World::Destroy(GameObjectHandle handle)
{
	//GameObject* endWorld = handle.Get();
	//endWorld->Terminate();
	//handle.Invalidate();

	if (!handle.IsValid())
	{
		return;
	}

	if (!mUpdating)
	{
		DestroyInternal(handle);
	}
	else
	{
		mDestroyList.push_back(handle);
	}

}

void World::Visit(WorldVisitor & visitor)
{
	for (auto gameObject : mUpdateList)
	{
		visitor(gameObject);
	}
}

void World::Update(f32 deltaTime)
{
	ASSERT(!mUpdating, "[World] Already updating the world.");

	//lock the update list
	mUpdating = true;

	//Re-compute size in case new objects are added to the update
	//list during iteration
	for (u32 i = 0; i < (u32)mUpdateList.size(); ++i)
	{
		GameObject* gameObject = mUpdateList[i];
		gameObject->Update(deltaTime);
	}

	//Unlock the update list
	mUpdating = false;

	//now we can safely destroy objects
	PurgeDestroyList();
}

void World::Render()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render();
	}
}

void World::Render2D()
{
	for (auto gameObject : mUpdateList)
	{
		gameObject->Render2D();
	}
}

void World::DestroyInternal(GameObjectHandle handle)
{
	ASSERT(!mUpdating, "[World] Cannot destroy game objects during update");

	//if handle is invalid, nothing to do so just exit
	if (!handle.IsValid())
	{
		return;
	}

	//terminate the game object
	GameObject* gameObject = handle.Get();
	gameObject->Terminate();

	//first remove it from the update list
	auto iter = std::find(mUpdateList.begin(), mUpdateList.end(), gameObject);
	if (iter != mUpdateList.end())
	{
		mUpdateList.erase(iter);
	}

	//next destroy the gameobject
	mGameObjectFactory.Destory(handle);
}

void World::PurgeDestroyList()
{
	for (auto handle : mDestroyList)
	{
		DestroyInternal(handle);
	}
	mDestroyList.clear();
}
