#ifndef INCLUDED_ENGINE_METAFIELD_H
#define INCLUDED_ENGINE_METAFIELD_H

class MetaType;

class MetaField
{
public:
	MetaField(const char* name, const MetaType* type, u32 offset);

	const char* GetName() const			{ return mName; }
	const MetaType* GetMetaType() const { return mType; }
	u32 GetOffset() const				{ return mOffset; }

private:
	const char* mName;
	const MetaType* mType;
	const u32 mOffset;
};

//----------------------------------------------------------------------------------------------------

template <typename ClassType, typename DataType>
inline const MetaType* DeduceMemberDataType(DataType ClassType::*)
{
	return DeduceDataType<DataType>();
}

//----------------------------------------------------------------------------------------------------

template <typename ClassType, typename DataType>
inline u32 GetFieldOffset(DataType ClassType::* field)
{
	return (u32)(void*)&(((ClassType*)nullptr)->*field);
}
#endif // #ifndef INCLUDED_ENGINE_METAFIELD_H