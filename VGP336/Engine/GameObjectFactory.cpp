#include "Precompiled.h"

#include "GameObjectFactory.h"
#include "tinyxml.h"

//components
#include "TransformComponent.h"
#include "ColliderComponent.h"
#include "CameraComponent.h"
#include "CameraControllerComponent.h"
#include "RTSCameraControllerComponent.h"
#include "SpriteComponent.h"
#include "TerrainComponent.h"
#include "ModelComponent.h"
#include "CursorComponent.h"
#include "AIComponent.h"
#include "SpawnerComponent.h"
#include "TowerComponent.h"
#include "HealthComponent.h"
#include "TeamComponent.h"
#include "BulletComponent.h"
#include "BuilderComponent.h"

//Add components to the gameobjects
namespace
{
	void AddTransformComponent(TiXmlElement*& pElem, GameObject*& gameObject)
	{
		TransformComponent* transformComponent = new TransformComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if component include these variables
			if (pName == "Position")
			{
				float pos[3];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				//get position
				for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set position for component
				transformComponent->SetPosition(Math::Vector3(pos[0], pos[1], pos[2]));
			}
		}
		gameObject->AddComponent(transformComponent);
	}

	void AddColliderComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		ColliderComponent* colliderComponent = new ColliderComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if components include these variables
			if (pName == "Center")
			{
				float center[3];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					//get center
					center[i] = strtof(pTemp2->GetText(), 0);
				}
				//set center for component
				colliderComponent->SetCenter(Math::Vector3(center[0], center[1], center[2]));
			}
			if (pName == "Extend")
			{
				float extend[3];
				TiXmlElement* pTemp3 = pTemp1->FirstChild()->ToElement();
				for (int i = 0; i < 3; pTemp3 = pTemp3->NextSiblingElement(), i++)
				{
					extend[i] = strtof(pTemp3->GetText(), 0);
				}
				colliderComponent->SetExtend(Math::Vector3(extend[0], extend[1], extend[2]));
			}
			if (pName == "Color")
			{
				float color[4];
				TiXmlElement* pTemp4 = pTemp1->FirstChild()->ToElement();
				for (int i = 0; i < 4; pTemp4 = pTemp4->NextSiblingElement(), i++)
				{
					color[i] = strtof(pTemp4->GetText(), 0);
				}
				colliderComponent->SetColor(Color(color[0]
					, color[1]
					, color[2]
					, color[3]));
			}
		}
		gameObject->AddComponent(colliderComponent);
	}

	void AddCameraComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		CameraComponent* cameraComponent = new CameraComponent();
		TiXmlElement* pTemp1 = pElem;

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//If the component does not include any variables, exit this loop
			if (!pTemp1->Attribute("name"))
			{
				break;
			}

			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if component include these variables
			if (pName == "Setup")
			{
				f32 pos[4];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				//get position
				for (int i = 0; i < 4; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set position for component
				cameraComponent->Setup(pos[0], pos[1], pos[2], pos[3]);
			}
			if (pName == "Position")
			{
				float pos[3];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				//get position
				for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set position for component
				cameraComponent->SetPosition(Math::Vector3(pos[0], pos[1], pos[2]));
			}
			if (pName == "Direction")
			{
				float pos[3];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				//get position
				for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set position for component
				cameraComponent->SetDirection(Math::Vector3(pos[0], pos[1], pos[2]));
			}
			if (pName == "LookAt")
			{
				float pos[3];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				//get position
				for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set position for component
				cameraComponent->SetLookAt(Math::Vector3(pos[0], pos[1], pos[2]));
			}
			if (pName == "FOV")
			{
				float fov;
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				fov = strtof(pTemp2->GetText(), 0);

				//set fov for component
				cameraComponent->SetFOV(fov);
			}
		}
		gameObject->AddComponent(cameraComponent);
	}

	void AddCameraControllerComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		CameraControllerComponent* cameraControllerComponent = new CameraControllerComponent();
		gameObject->AddComponent(cameraControllerComponent);
	}
	
	void AddRTSCameraControllerComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		RTSCameraControllerComponent* rtsCameraControllerComponent = new RTSCameraControllerComponent();
		gameObject->AddComponent(rtsCameraControllerComponent);
	}

	void AddTerrainComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		TerrainComponent* terrainComponent = new TerrainComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();
		std::string fileName;
		std::wstring textureFileName;
		int params1[3];
		int params2[3];
		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName1 = pTemp1->Attribute("name");
			
			if (pName1 == "Filename") 
			{
				fileName = pTemp1->GetText();
			}
			if (pName1 == "TextureFilename")
			{
				std::string a = pTemp1->GetText();
				std::wstring b(a.begin(), a.end());
				textureFileName = b;
			}
			if (pName1 == "Width")
			{
				params1[0] = atoi(pTemp1->GetText());
			}
			if (pName1 == "Length")
			{
				params1[1] = atoi(pTemp1->GetText());
			}
			if (pName1 == "Layer")
			{
				params1[2] = atoi(pTemp1->GetText());
			}
			if (pName1 == "MaxHeight")
			{
				params2[0] = strtof(pTemp1->GetText(), 0);
			}
			if (pName1 == "MinHeight")
			{
				params2[1] = strtof(pTemp1->GetText(), 0);
			}
			if (pName1 == "Frequency")
			{
				params2[2] = strtof(pTemp1->GetText(), 0);
			}
		}
		terrainComponent->SetTerrain(fileName, params1[0], params1[1], params2[0]);
		terrainComponent->SetLayer(textureFileName, params1[2], params2[1], params2[0]);
		gameObject->AddComponent(terrainComponent);
	}

	void AddModelComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		ModelComponent* modelComponent = new ModelComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();
		std::string fileName;

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName1 = pTemp1->Attribute("name");

			if (pName1 == "Filename")
			{
				fileName = pTemp1->GetText();
			}
		}
		modelComponent->SetModel(fileName);
		gameObject->AddComponent(modelComponent);
	}

	void AddCursorComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		CursorComponent* cursorComponent = new CursorComponent();
		gameObject->AddComponent(cursorComponent);
	}

	void AddSpriteComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		SpriteComponent* spriteComponent = new SpriteComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if components include these variables
			if (pName == "Position")
			{
				float pos[2];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				for (int i = 0; i < 2; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					//get center
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set center for component
				spriteComponent->SetPosition(Math::Vector2(pos[0], pos[1]));
			}
			if (pName == "TextureName")
			{
				std::string name;
				name = pTemp1->GetText();
				spriteComponent->SetTextureName(name.c_str());
			}
		}
		gameObject->AddComponent(spriteComponent);
	}
	
	void AddAIComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		AIComponent* aiComponent = new AIComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if components include these variables
			if (pName == "Destination")
			{
				float pos[3];
				TiXmlElement* pTemp2 = pTemp1->FirstChild()->ToElement();
				for (int i = 0; i < 3; pTemp2 = pTemp2->NextSiblingElement(), i++)
				{
					//get center
					pos[i] = strtof(pTemp2->GetText(), 0);
				}
				//set center for component
				aiComponent->SetDestination(Math::Vector3(pos[0], pos[1], pos[2]));
			}
		}
		gameObject->AddComponent(aiComponent);
	}
	
	void AddSpawnerComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		SpawnerComponent* spawnerComponent = new SpawnerComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if components include these variables
			if (pName == "FileName")
			{
				std::string name;
				name = pTemp1->GetText();
				spawnerComponent->SetTemplatename(name.c_str());
			}
			if (pName == "ObjectName")
			{
				std::string name;
				name = pTemp1->GetText(); 
				spawnerComponent->SetObjectname(name.c_str());
			}
			if (pName == "Cooldown")
			{
				spawnerComponent->SetCooldown(strtof(pTemp1->GetText(), 0));
			}
			if (pName == "UnitSpeed")
			{
				spawnerComponent->SetUnitSpeed(strtof(pTemp1->GetText(), 0));
			}
		}
		gameObject->AddComponent(spawnerComponent);
	}

	void AddTowerComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		TowerComponent* towerComponent = new TowerComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");

			//Check if components include these variables
			if (pName == "FileName")
			{
				std::string name;
				name = pTemp1->GetText();
				towerComponent->SetTemplateName(name.c_str());
			}
			if (pName == "FireRate")
			{
				towerComponent->SetFireRate(strtof(pTemp1->GetText(), 0));
			}
		}
		gameObject->AddComponent(towerComponent);
	}

	void AddHealthComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		HealthComponent* healthComponent = new HealthComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");
			if (pName == "MaxHealth")
			{
				healthComponent->SetMaxHealth(strtof(pTemp1->GetText(), 0));
			}
		}
		gameObject->AddComponent(healthComponent);
	}
	
	void AddTeamComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		TeamComponent* teamComponent = new TeamComponent();
		TiXmlElement* pTemp1 = pElem->FirstChild()->ToElement();

		//Iterate through the components nodes
		for (pTemp1; pTemp1; pTemp1 = pTemp1->NextSiblingElement())
		{
			//Get component's variables
			std::string pName = pTemp1->Attribute("name");
			if (pName == "TeamID")
			{
				teamComponent->SetTeamId(atoi(pTemp1->GetText()));
			}
		}
		gameObject->AddComponent(teamComponent);
	}

	void AddBulletComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		BulletComponent* bulletComponent = new BulletComponent();
		gameObject->AddComponent(bulletComponent);
	}

	void AddBuilderComponent(TiXmlElement *& pElem, GameObject *& gameObject)
	{
		BuilderComponent* builderComponent = new BuilderComponent();
		gameObject->AddComponent(builderComponent);
	}
}

GameObjectFactory::GameObjectFactory(u16 capacity)
	:mGameObjectAllocator(capacity)
{
}

GameObjectHandle GameObjectFactory::Create(const char* templateFilename)
{
	GameObjectHandle handle = mGameObjectAllocator.New();
	GameObject* gameObject = handle.Get();

	////////////////////////////////////////////////////////////////////
	TiXmlDocument doc(templateFilename);
	VERIFY(doc.LoadFile(), "Failed to load file %s", templateFilename);
	
	TiXmlElement* pElem = doc.FirstChild()->ToElement();
	if (!pElem)
	{
		return handle;
	}

	TiXmlNode* hRoot = pElem;
	if ((std::string)pElem->Value() == "GameObject")
	{
		pElem = hRoot->FirstChild()->FirstChild()->ToElement();

		//Iterate through the gameObject components
		for (pElem; pElem; pElem = pElem->NextSiblingElement())
		{
			//Check if There is a transform component
			if ((std::string)pElem->Value() == "TransformComponent")
			{
				AddTransformComponent(pElem, gameObject);
			}
			//Check if There is a collider component
			if ((std::string)pElem->Value() == "ColliderComponent")
			{
				AddColliderComponent(pElem, gameObject);
			}
			//Check if There is a camera component
			if ((std::string)pElem->Value() == "CameraComponent")
			{
				AddCameraComponent(pElem, gameObject);
			}
			//Check if There is a camera controller component
			if ((std::string)pElem->Value() == "CameraControllerComponent")
			{
				AddCameraControllerComponent(pElem, gameObject);
			}
			//Check if There is a camera controller component
			if ((std::string)pElem->Value() == "RTSCameraControllerComponent")
			{
				AddRTSCameraControllerComponent(pElem, gameObject);
			}
			//Check if There is a terrain component
			if ((std::string)pElem->Value() == "TerrainComponent")
			{
				AddTerrainComponent(pElem, gameObject);
			}
			//Check if There is a model component
			if ((std::string)pElem->Value() == "ModelComponent")
			{
				AddModelComponent(pElem, gameObject);
			}
			//Check if There is a sprite component
			if ((std::string)pElem->Value() == "SpriteComponent")
			{
				AddSpriteComponent(pElem, gameObject);
			}
			//Check if There is a cursor component
			if ((std::string)pElem->Value() == "CursorComponent")
			{
				AddCursorComponent(pElem, gameObject);
			}
			//Check if There is a AI component
			if ((std::string)pElem->Value() == "AIComponent")
			{
				AddAIComponent(pElem, gameObject);
			}
			//Check if There is a Spawner component
			if ((std::string)pElem->Value() == "SpawnerComponent")
			{
				AddSpawnerComponent(pElem, gameObject);
			}
			//Check if There is a Tower component
			if ((std::string)pElem->Value() == "TowerComponent")
			{
				AddTowerComponent(pElem, gameObject);
			}
			//Check if There is a Health component
			if ((std::string)pElem->Value() == "HealthComponent")
			{
				AddHealthComponent(pElem, gameObject);
			}
			//Check if There is a Team component
			if ((std::string)pElem->Value() == "TeamComponent")
			{
				AddTeamComponent(pElem, gameObject);
			}
			//Check if There is a Bullet component
			if ((std::string)pElem->Value() == "BulletComponent")
			{
				AddBulletComponent(pElem, gameObject);
			}
			//Check if There is a Builder component
			if ((std::string)pElem->Value() == "BuilderComponent")
			{
				AddBuilderComponent(pElem, gameObject);
			}
		}
	}
	return handle;
}

void GameObjectFactory::Destory(GameObjectHandle handle)
{
	mGameObjectAllocator.Delete(handle);
}