#ifndef INCLUDED_ENGINE_METATYPE_H
#define INCLUDED_ENGINE_METATYPE_H

class MetaType
{
public:
	typedef void* (*CreateFunc)();
	typedef void (*DestroyFunc)(void*);

	enum class Type
	{
		Int,
		Float,
		Bool,
		String,
		Vector3,
		Color,
		Class
	};

	MetaType(const char* name, Type type, u32 size, CreateFunc create, DestroyFunc destroy);
	
	const char* GetName() const		{ return mName; }
	Type GetType() const			{ return mType; }
	u32 GetSize() const				{ return mSize; }

	void* Create() const			{ return mCreate(); }
	void Destroy(void* data) const	{ mDestroy(data); }

	NONCOPYABLE(MetaType);

private:
	const char* mName;
	const Type mType;
	const u32 mSize;

	CreateFunc mCreate;
	DestroyFunc mDestroy;
};

//====================================================================================================
// Helper Functions
//====================================================================================================

template <typename DataType>
const MetaType* DeduceDataType();

#endif // #ifndef INCLUDED_ENGINE_METATYPE_H