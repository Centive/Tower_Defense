#ifndef INCLUDED_META_H
#define INCLUDED_META_H

#include "MetaType.h"

#include "MetaField.h"
#include "MetaClass.h"

#include "MetaRegistration.h"
#include "MetaRegistry.h"

//====================================================================================================
// Macros
//====================================================================================================

#define META_CLASS_DECLARE\
	static const MetaClass* StaticGetMetaClass();\
	virtual const MetaClass* GetMetaClass() const { return StaticGetMetaClass(); }

#define META_CLASS_BEGIN_INTERNAL(ClassType)\
	namespace {\
		void* Create##ClassType()			{ return new ClassType(); }\
		void Destroy##ClassType(void* data)	{ delete static_cast<ClassType*>(data); }\
	}\
	const MetaClass* ClassType::StaticGetMetaClass()\
	{\
		typedef ClassType LocalType;\
		const char* className = #ClassType;\
		MetaType::CreateFunc Create = Create##ClassType;\
		MetaType::DestroyFunc Destroy = Destroy##ClassType;

#define META_DERIVED_BEGIN(ClassType, ParentType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const MetaClass* parentMetaClass = ParentType::StaticGetMetaClass();

#define META_CLASS_BEGIN(ClassType)\
	META_CLASS_BEGIN_INTERNAL(ClassType)\
		const MetaClass* parentMetaClass = nullptr;

#define META_FIELD_BEGIN\
		static const MetaField fields[] = {

#define META_FIELD(Field, Name)\
			MetaField(Name, DeduceMemberDataType(&LocalType::Field), GetFieldOffset(&LocalType::Field)),

#define META_FIELD_END\
		};\
		static const u32 numFields = sizeof(fields) / sizeof(fields[0]);

#define META_NO_FIELD\
		const MetaField* fields = nullptr;\
		const u32 numFields = 0;

#define META_CLASS_END\
		static const MetaClass sMetaClass(className, sizeof(LocalType), Create, Destroy, parentMetaClass, fields, numFields);\
		return &sMetaClass;\
	}

#endif // #ifndef INCLUDED_META_H