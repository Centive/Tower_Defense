#include "Precompiled.h"

#include "MetaType.h"

#include "Color.h"
#include "EngineMath.h"

MetaType::MetaType(const char* name, Type type, u32 size, CreateFunc create, DestroyFunc destroy)
	: mName(name)
	, mType(type)
	, mSize(size)
	, mCreate(create)
	, mDestroy(destroy)
{}

#define META_REGISTER_TYPE(Name, DataType)\
	namespace Meta { namespace Detail {\
		void* Create##Name()			{ return new DataType; }\
		void Destroy##Name(void* data)	{ delete static_cast<DataType*>(data); }\
	}}\
	template <> const MetaType* DeduceDataType<DataType>()\
	{\
		static MetaType sMetaType(#Name, MetaType::Type::##Name, sizeof(DataType),\
								  Meta::Detail::Create##Name,\
								  Meta::Detail::Destroy##Name);\
		return &sMetaType;\
	}

META_REGISTER_TYPE(Int, s32);
META_REGISTER_TYPE(Float, f32);
META_REGISTER_TYPE(Bool, bool);
META_REGISTER_TYPE(String, std::string);
META_REGISTER_TYPE(Vector3, Math::Vector3);
META_REGISTER_TYPE(Color, Color);