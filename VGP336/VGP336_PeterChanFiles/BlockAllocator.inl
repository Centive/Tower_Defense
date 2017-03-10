//====================================================================================================
// Filename:	BlockAllocator.inl
// Created by:	Peter Chan
//====================================================================================================

//====================================================================================================
// Class Definitions
//====================================================================================================

template <typename T>
BlockAllocator<T>::BlockAllocator(u16 capacity)
	: mFreeSlot(0)
	, mCapacity(capacity)
	, mData(nullptr)
	, mGenerations(nullptr)
{
	// Preallocate memory and assign next slot indices
	mData = (T*)malloc(capacity * sizeof(T));
	for (u16 i = 0; i < capacity - 1; ++i)
	{
		*((s32*)(mData + i)) = (s32)i + 1;
	}
	*((s32*)(mData + capacity - 1)) = -1;

	// Every slot starts at generation 0
	mGenerations = (u16*)malloc(capacity * sizeof(u16));
	memset(mGenerations, 0, capacity * sizeof(u16));

	// Register itself with handle class
	Handle<T>::sAllocator = this;
}

//----------------------------------------------------------------------------------------------------

template <typename T>
BlockAllocator<T>::~BlockAllocator()
{
	// Unregister itself with handle class
	if (Handle<T>::sAllocator == this)
	{
		Handle<T>::sAllocator = nullptr;
	}

	// Free all memory
	free(mData);
	free(mGenerations);
}

//----------------------------------------------------------------------------------------------------

template <typename T>
Handle<T> BlockAllocator<T>::New()
{
	// Check if we have more free slots
	Handle<T> handle;
	if (mFreeSlot == -1)
	{
		return handle;
	}

	// Get current free slot
	handle.mIndex = (u16)mFreeSlot;
	handle.mGeneration = mGenerations[mFreeSlot];

	// Track the next free slot
	mFreeSlot = *((s32*)(mData + mFreeSlot));

	// Initialize slot
	new (mData + handle.mIndex) T();

	// Return handle
	return handle;
}

//----------------------------------------------------------------------------------------------------

template <typename T>
void BlockAllocator<T>::Delete(Handle<T> handle)
{
	if (IsValid(handle))
	{
		// Invoke destructor
		mData[handle.mIndex].~T();

		// Invalidate all existing handles
		mGenerations[handle.mIndex]++;

		// Swap next free slot index
		*((s32*)(mData + handle.mIndex)) = mFreeSlot;
		mFreeSlot = (s32)handle.mIndex;
	}
}

//----------------------------------------------------------------------------------------------------

template <typename T>
bool BlockAllocator<T>::IsValid(Handle<T> handle) const
{
	const u16 index = handle.GetIndex();
	const u16 generation = handle.GetGeneration();
	return (index < mCapacity) && (generation == mGenerations[index]);
}

//----------------------------------------------------------------------------------------------------

template <typename T>
T* BlockAllocator<T>::Get(Handle<T> handle)
{
	if (!IsValid(handle))
	{
		return nullptr;
	}

	return mData + handle.mIndex;
}