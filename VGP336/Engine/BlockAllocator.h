#ifndef INCLUDED_ENGINE_BLOCKALLOCATOR_H
#define INCLUDED_ENGINE_BLOCKALLOCATOR_H

//====================================================================================================
// Filename:	BlockAllocator.h
// Created by:	Peter Chan
// Description:	Class for a typed block allocator.
//====================================================================================================

//====================================================================================================
// Includes
//====================================================================================================

#include "Handle.h"

//====================================================================================================
// Class Declarations
//====================================================================================================

template <typename T>
class BlockAllocator
{
public:
	BlockAllocator(u16 capacity);
	~BlockAllocator();

	Handle<T> New();
	void Delete(Handle<T> handle);
	
	bool IsValid(Handle<T> handle) const;

	T* Get(Handle<T> handle);

private:
	s32 mFreeSlot;
	u16 mCapacity;
	T* mData;
	u16* mGenerations;
};

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "BlockAllocator.inl"

#endif // #ifndef INCLUDED_ENGINE_BLOCKALLOCATOR_H