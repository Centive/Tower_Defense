//====================================================================================================
// Filename:	XMLReader.cpp
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Precompiled.h"

#include "XMLReader.h"

#include "Color.h"
#include "EngineMath.h"
#include "Utils.h"
#include <tinyxml.h>

//====================================================================================================
// Local Definitions
//====================================================================================================

namespace
{
	bool Read(int* instance, const TiXmlNode* node)
	{
		*instance = atoi(node->Value());
		return true;
	}
	
	bool Read(float* instance, const TiXmlNode* node)
	{
		*instance = (float)atof(node->Value());
		return true;
	}
	
	bool Read(bool* instance, const TiXmlNode* node)
	{
		*instance = Utils::Compare(node->Value(), "true");
		return true;
	}
	
	bool Read(std::string* instance, const TiXmlNode* node)
	{
		*instance = node->Value();
		return true;
	}
	
	bool Read(Math::Vector3* instance, const TiXmlNode* node)
	{
		if (node->FirstChild() == nullptr ||
			node->NextSibling() == nullptr ||
			node->NextSibling()->FirstChild() == nullptr ||
			node->NextSibling()->NextSibling() == nullptr ||
			node->NextSibling()->NextSibling()->FirstChild() == nullptr)
		{
			return false;
		}

		Read(&(instance->x), node->FirstChild());
		Read(&(instance->y), node->NextSibling()->FirstChild());
		Read(&(instance->z), node->NextSibling()->NextSibling()->FirstChild());
		return true;
	}
	
	bool Read(Color* instance, const TiXmlNode* node)
	{
		if (node->FirstChild() == nullptr ||
			node->NextSibling() == nullptr ||
			node->NextSibling()->FirstChild() == nullptr ||
			node->NextSibling()->NextSibling() == nullptr ||
			node->NextSibling()->NextSibling()->FirstChild() == nullptr ||
			node->NextSibling()->NextSibling()->NextSibling() == nullptr ||
			node->NextSibling()->NextSibling()->NextSibling()->FirstChild() == nullptr)
		{
			return false;
		}

		Read(&(instance->r), node->FirstChild());
		Read(&(instance->g), node->NextSibling()->FirstChild());
		Read(&(instance->b), node->NextSibling()->NextSibling()->FirstChild());
		Read(&(instance->a), node->NextSibling()->NextSibling()->NextSibling()->FirstChild());
		return true;
	}

	bool Read(void* instance, const MetaType* metaType, const TiXmlNode* node)
	{
		if (node == nullptr)
		{
			return false;
		}

		switch (metaType->GetType())
		{
		case MetaType::Type::Int:		return Read((int*)instance, node);
		case MetaType::Type::Float:		return Read((float*)instance, node);
		case MetaType::Type::Bool:		return Read((bool*)instance, node);
		case MetaType::Type::String:	return Read((std::string*)instance, node);
		case MetaType::Type::Vector3:	return Read((Math::Vector3*)instance, node);
		case MetaType::Type::Color:		return Read((Color*)instance, node);
		case MetaType::Type::Class:		return XMLReader::Read(instance, (const MetaClass*)metaType, node);
		}
	
		return false;
	}
}

//====================================================================================================
// Class Definitions
//====================================================================================================

bool XMLReader::Read(void* instance, const MetaClass* metaClass, const TiXmlNode* node)
{
	while (node != nullptr)
	{
		const TiXmlElement* element = node->ToElement();
		if (element != nullptr)
		{
			const char* fieldName = element->Attribute("name");
			const MetaField* metaField = metaClass->FindField(fieldName);
			if (metaField != nullptr)
			{
				void* member = (u8*)instance + metaField->GetOffset();
				bool success = ::Read(member, metaField->GetMetaType(), element->FirstChild());
				if (!success)
				{
					return false;
				}
			}
		}

		node = node->NextSibling();
	}

	return true;
}