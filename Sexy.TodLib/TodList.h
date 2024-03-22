#ifndef __TODLIST_H__
#define __TODLIST_H__

#define MAX_GLOBAL_ALLOCATORS 128

#include "TodDebug.h"

struct TodAllocator
{
    void*				mFreeList;
    void*				mBlockList;
    int					mGrowCount;
    int					mTotalItems;
    int					mItemSize;

    void                Initialize(int theGrowCount, int theItemSize);
    void                Dispose();
    void                FreeAll();
    void*               Alloc(int theItemSize);
    void*               Calloc(int theItemSize);
    void                Free(void* theItem, int theItemSize);
    void                Grow();
    bool                IsPointerFromAllocator(void* theItem);
    bool                IsPointerOnFreeList(void* theItem);
};
extern int gNumGlobalAllocators;
extern TodAllocator gGlobalAllocators[MAX_GLOBAL_ALLOCATORS];

template <typename T> class TodListNode
{
public:
	T					mValue;
	TodListNode<T>*		mNext;
	TodListNode<T>*		mPrev;
};

template <typename T> class TodList
{
public:
	TodListNode<T>*		mHead;
	TodListNode<T>*		mTail;
	int					mSize;
	TodAllocator*		mpAllocator;

public:
    TodList<T>()
    {
        mHead = nullptr;
        mTail = nullptr;
        mSize = 0;
        mpAllocator = nullptr;
    }

    ~TodList<T>()
    {
        RemoveAll();
    }

    TodListNode<T>* GetHead()
    {
        TOD_ASSERT(mHead != nullptr);
        return mHead;
    }

    TodListNode<T>* GetTail()
    {
        TOD_ASSERT(mTail != nullptr);
        return mTail;
    }

    void AddHead(const T& theHead)
    {
        if (mpAllocator == nullptr)
            mpAllocator = FindGlobalAllocator(sizeof(TodListNode<T>));

        TodListNode<T>* aNode = (TodListNode<T>*)mpAllocator->Calloc(sizeof(TodListNode<T>));
        if (aNode)
            aNode->mValue = theHead;
        aNode->mNext = mHead;  // The next node of the new node points to the original node
        aNode->mPrev = nullptr;  // The new node serves as the head and there is no previous node.
        if (mHead)
            mHead->mPrev = aNode;  // When a head node already exists, make the previous node of the original head node point to the new node.
        else
            mTail = aNode;  // When there is no head node, the tail node is also the new node.
        mSize++;
        mHead = aNode;
    }

    void AddTail(const T& theTail)
    {
        if (mpAllocator == nullptr)
            mpAllocator = FindGlobalAllocator(sizeof(TodListNode<T>));

        TodListNode<T>* aNode = (TodListNode<T>*)mpAllocator->Calloc(sizeof(TodListNode<T>));
        if (aNode)
            aNode->mValue = theTail;
        aNode->mNext = nullptr;
        aNode->mPrev = mTail;
        if (mTail)
            mTail->mNext = aNode;
        else
            mHead = aNode;
        mSize++;
        mTail = aNode;
    }

    inline T RemoveHead()
    {
        TodListNode<T>* aHead = mHead;
        TodListNode<T>* aSecNode = aHead->mNext;
        mHead = aSecNode;
        if (aSecNode)
            aSecNode->mPrev = nullptr;
        else
            mTail = nullptr;
        
        T aVal = aHead->mValue;
        mSize--;
        mpAllocator->Free(aHead, sizeof(TodListNode<T>));
        return aVal;
    }

    inline TodListNode<T>* RemoveAt(TodListNode<T>* theNode)
    {
        if (theNode->mPrev != nullptr)
            theNode->mPrev->mNext = theNode->mNext;
        else
            mHead = theNode->mNext;

        if (theNode->mNext != nullptr)
            theNode->mNext->mPrev = theNode->mPrev;
        else
            mTail = theNode->mPrev;

        mSize--;
        mpAllocator->Free(theNode, sizeof(TodListNode<T>));
        return theNode->mNext;
    }

    inline TodListNode<T>* Find(const T& theItem) const
    {
        for (TodListNode<T>* aNode = mHead; aNode != nullptr; aNode = aNode->mNext)
            if (aNode->mValue == theItem)
                return aNode;
        return nullptr;
    }

    inline void RemoveAll()
    {
        TodListNode<T>* aNode = mHead;
        while (aNode)
        {
            TodListNode<T>* temp = aNode;
            aNode = aNode->mNext;
            mpAllocator->Free(temp, sizeof(TodListNode<T>));
        }

        mSize = 0;
        mHead = nullptr;
        mTail = nullptr;
    }

    inline void SetAllocator(TodAllocator* theAllocator) 
    { 
        TOD_ASSERT(mSize == 0);
        mpAllocator = theAllocator;
    }
};

#endif
