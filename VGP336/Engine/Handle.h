#ifndef INCLUDED_ENGINE_HANDLE_H
#define INCLUDED_ENGINE_HANDLE_H

//====================================================================================================
// Filename:	Handle.h
// Created by:	Peter Chan
// Description:	Class for a typed memory handle.
//====================================================================================================

//====================================================================================================
// Forward Declarations
//====================================================================================================

template <typename T> class BlockAllocator;

//====================================================================================================
// Class Declarations
//====================================================================================================

template <typename T>
class Handle
{
public:
	Handle();

	bool IsValid() const;
	void Invalidate();

	T* Get();
	
	u16 GetIndex() const		{ return mIndex; }
	u16 GetGeneration() const	{ return mGeneration; }
	
private:
	friend class BlockAllocator<T>;

	static BlockAllocator<T>* sAllocator;

	u16 mIndex;
	u16 mGeneration;
};

//====================================================================================================
// Inline Definitions
//====================================================================================================

#include "Handle.inl"

#endif // #ifndef INCLUDED_ENGINE_HANDLE_H