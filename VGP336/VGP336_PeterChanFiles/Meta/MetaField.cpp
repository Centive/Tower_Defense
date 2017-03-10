#include "Precompiled.h"

#include "MetaField.h"

MetaField::MetaField(const char* name, const MetaType* type, u32 offset)
	: mName(name)
	, mType(type)
	, mOffset(offset)
{}