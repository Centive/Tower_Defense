#include "Precompiled.h"

#include "GameObjectFactory.h"

#include "GameObject.h"
#include "Meta.h"
#include "Utils.h"
#include "XMLReader.h"
#include <tinyxml.h>

GameObjectFactory::GameObjectFactory(GameObjectAllocator& allocator)
	: mGameObjectAllocator(allocator)
{
}

GameObjectHandle GameObjectFactory::Create(const char* templateFilename)
{
	GameObjectHandle handle = mGameObjectAllocator.New();
	GameObject* gameObject = handle.Get();

	TiXmlDocument templateDoc;
	VERIFY(templateDoc.LoadFile(templateFilename), "[GameObjectFactory] Failed to open template file '%s'.", templateFilename);

	const TiXmlNode* gameObjectNode = templateDoc.FirstChild();
	if (Utils::Compare(gameObjectNode->Value(), "GameObject"))
	{
		const TiXmlNode* componentsNode = gameObjectNode->FirstChild();
		if (Utils::Compare(componentsNode->Value(), "Components"))
		{
			const TiXmlNode* nextComponentNode = componentsNode->FirstChild();
			while (nextComponentNode != nullptr)
			{
				const char* componentName = nextComponentNode->Value();

				const MetaClass* metaClass = MetaRegistry::GetMetaClass(componentName);
				if (metaClass == nullptr)
				{
					LOG("Class [%s] not registered with the meta system.", componentName);
				}
				else
				{
					void* newComponent = metaClass->Create();
					const TiXmlNode* data = nextComponentNode->FirstChild();
					VERIFY(XMLReader::Read(newComponent, metaClass, data), "Failed to read %s.", componentName);
					gameObject->AddComponent((Component*)newComponent);
				}

				nextComponentNode = nextComponentNode->NextSibling();
			}
		}
	}

	return handle;
}

void GameObjectFactory::Destroy(GameObjectHandle handle)
{
	if (handle.IsValid())
	{
		// This will automatically invalidate all existing handle to this object
		mGameObjectAllocator.Delete(handle);
	}
}