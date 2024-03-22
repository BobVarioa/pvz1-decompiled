#include "TodList.h"
#include "TodDebug.h"
#include "TodCommon.h"
#include "../SexyAppFramework/Debug.h"

void TodAllocator::Initialize(int theGrowCount, int theItemSize)
{
	TOD_ASSERT(theItemSize >= sizeof(void*));

	mFreeList = nullptr;
	mBlockList = nullptr;
	mGrowCount = theGrowCount;
	mTotalItems = 0;
	mItemSize = theItemSize;
}

void TodAllocator::Dispose()
{
	FreeAll();
}

//0x4438C0
void TodAllocator::Grow()
{
	TOD_ASSERT(mGrowCount > 0);
	TOD_ASSERT(mItemSize >= sizeof(void*));

	void* aBlock = TodMalloc(mGrowCount * mItemSize + 4);
	*(void**)aBlock = mBlockList;
	mBlockList = aBlock;

	void* aFreeList = mFreeList;
	void* aItem = (void*)((uint)aBlock + 4);
	for (int i = 0; i < mGrowCount; i++)
	{
		*(void**)aItem = aFreeList;
		aFreeList = aItem;
		aItem = (void*)((uint)aItem + mItemSize);
	}
	mFreeList = aFreeList;
}

bool TodAllocator::IsPointerFromAllocator(void* theItem)
{
	size_t aBlockSize = mGrowCount * mItemSize;  // The memory size of each "Grow", that is, the memory size of each block
	for (void* aPtr = mBlockList; aPtr != nullptr; aPtr = *(void**)aPtr)
	{
		uint aItemPtr = (uint)theItem;
		// The first four bytes of the block are an additional area allocated to store the pointer to the next block.
		uint aBlockPtr = (uint)aPtr + sizeof(void*);
		// Determine whether theItem is located in the current block and points to the starting address of the area of ​​an item
		if (aItemPtr >= aBlockPtr && aItemPtr < aBlockPtr + aBlockSize && (aItemPtr - aBlockPtr) % mItemSize == 0)
			return true;
	}
	return false;
}

bool TodAllocator::IsPointerOnFreeList(void* theItem)
{
	for (void* aPtr = mFreeList; aPtr != nullptr; aPtr = *(void**)aPtr)
		if (theItem == aPtr)
			return true;
	return false;
}

void* TodAllocator::Alloc(int theItemSize)
{
	mTotalItems++;
	if (mFreeList == nullptr)
		Grow();

	void* anItem = (void*)mFreeList;
	mFreeList = *(void**)anItem;
	return anItem;
}

void* TodAllocator::Calloc(int theItemSize)
{
	void* anItem = Alloc(theItemSize);
	memset(anItem, 0, theItemSize);
	return anItem;
}

void TodAllocator::Free(void* theItem, int theItemSize)
{
	mTotalItems--;
	TOD_ASSERT(IsPointerFromAllocator(theItem));
	TOD_ASSERT(!IsPointerOnFreeList(theItem));
	*(void**)theItem = mFreeList;  // Store the original available area header in [*theItem]
	mFreeList = theItem;  // Set theItem as the new available area header
}

void TodAllocator::FreeAll()
{
	for (void* aBlock = mBlockList; aBlock != nullptr; )
	{
		void* aNext = *(void**)aBlock;
		TodFree(aBlock);
		aBlock = aNext;
	}

	mBlockList = nullptr;
	mFreeList = nullptr;
	mTotalItems = 0;
}
