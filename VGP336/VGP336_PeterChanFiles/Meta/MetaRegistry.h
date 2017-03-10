#ifndef INCLUDED_ENGINE_METAREGISTRY_H
#define INCLUDED_ENGINE_METAREGISTRY_H

//====================================================================================================
// Filename:	MetaRegistry.h
// Created by:	Peter Chan
// Description:	Meta class registry.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

class MetaClass;

//====================================================================================================
// Function Declarations
//====================================================================================================

namespace MetaRegistry
{

void Register(const MetaClass* metaClass);

const MetaClass* GetMetaClass(const char* className);

}

#endif // #ifndef INCLUDED_ENGINE_METAREGISTRY_H