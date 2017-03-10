#include "Precompiled.h"

#include "MetaRegistry.h"

#include "Hash.h"
#include "MetaClass.h"

namespace
{
	typedef std::map<u64, const MetaClass*> MetaClassMap;

	MetaClassMap sMetaClasses;
}

void MetaRegistry::Register(const MetaClass* metaClass)
{
	const u64 key = GetHash(metaClass->GetName());
	sMetaClasses.insert(std::make_pair(key, metaClass));
}

const MetaClass* MetaRegistry::GetMetaClass(const char* className)
{
	const u64 key = GetHash(className);
	auto iter = sMetaClasses.find(key);
	ASSERT(iter != sMetaClasses.end(), "[MetaRegistry] Meta class for %s not found.", className);
	return iter->second;
}