#include "Precompiled.h"

#include "MetaClass.h"

#include "MetaField.h"

MetaClass::MetaClass(const char* name, u32 size,
					 MetaType::CreateFunc create,
					 MetaType::DestroyFunc destroy,
					 const MetaClass* parent,
					 const MetaField* fields, u32 numFields)
	: MetaType(name, MetaType::Type::Class, size, create, destroy)
	, mParent(parent)
	, mFields(fields)
	, mNumFields(numFields)
{}
	
const MetaField* MetaClass::FindField(const char* name) const
{
	const MetaField* field = nullptr;
	for (u32 i = 0; i < mNumFields; ++i)
	{
		const MetaField& f = mFields[i];
		if (strcmp(f.GetName(), name) == 0)
		{
			field = &f;
			break;
		}
	}

	// If the field is not found, try the parent
	if (field == nullptr && mParent != nullptr)
	{
		field = mParent->FindField(name);
	}
	return field;
}