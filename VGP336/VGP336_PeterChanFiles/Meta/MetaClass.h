#ifndef INCLUDED_ENGINE_METACLASS_H
#define INCLUDED_ENGINE_METACLASS_H

#include "MetaType.h"

class MetaField;

class MetaClass : public MetaType
{
public:
	MetaClass(const char* name, u32 size,
			  MetaType::CreateFunc create,
			  MetaType::DestroyFunc destroy,
			  const MetaClass* parent,
			  const MetaField* fields, u32 numFields);

	const MetaClass* GetParent() const { return mParent; }
	
	const MetaField* FindField(const char* name) const;

private:
	const MetaClass* mParent;
	const MetaField* mFields;
	const u32 mNumFields;
};

#endif // #ifndef INCLUDED_ENGINE_METACLASS_H