#ifndef __PRIORITY_QUEUE_HEADER_INCLUDED__
#define __PRIORITY_QUEUE_HEADER_INCLUDED__

#include "DynamicArray.h"
#include "Iterator.h"
#include "PriorityQueueHandle.h"

template <class Item, class Key, class HandleUpdator, class KeyAccessor>
class PriorityQueue
{
public:
	PriorityQueue();
	PriorityQueue(Iterator<Item*>& itemsIterator, size_t itemsCount);
	PriorityQueue(const PriorityQueue<Item, Key, HandleUpdator, KeyAccessor>&) = default;
	PriorityQueue(PriorityQueue<Item, Key, HandleUpdator, KeyAccessor>&& source);
	PriorityQueue<Item, Key, HandleUpdator, KeyAccessor>&
		operator=(const PriorityQueue<Item, Key, HandleUpdator, KeyAccessor>&) = default;
	PriorityQueue<Item, Key, HandleUpdator, KeyAccessor>&
		operator=(PriorityQueue<Item, Key, HandleUpdator, KeyAccessor>&& rhs);
	~PriorityQueue();

	void add(Item* item);
	Item* extractMin();
	const Item* getMin() const;
	void decreaseKey(const PriorityQueueHandle& handleToItem, const Key& newKey);
	void empty();
	bool isEmpty() const;

private:
	static size_t computeLeftChildOf(size_t index);
	static size_t computeParentOf(size_t index);
	static bool isRoot(size_t index);

private:
	void buildHeap();
	void siftDownItemAt(size_t index);
	void siftUpItemAt(size_t index);
	void addAtEnd(Item* newItem);
	void setItemAtWith(size_t index, Item* item);
	void invalidateAllHandles();
	void invalidateHandleAt(size_t index);
	void setHandleAtWith(size_t index, const PriorityQueueHandle& handle);
	void setKeyAtWith(size_t index, const Key& newKey);
	size_t computeMinKeySuccessor(size_t leftSuccessor) const;
	bool compare(const Item& lhs, const Item& rhs) const;
	bool isWithinHeap(size_t index) const;
	void copyItems(Iterator<Item*>& itemsIterator, size_t itemsCount);
	void swapContentsWith(PriorityQueue<Item, Key, HandleUpdator, KeyAccessor> priorityQueue);

private:
	DynamicArray<Item*> items;
	size_t itemsCount;
	HandleUpdator handleUpdator;
	KeyAccessor keyAccessor;
};

#include "PriorityQueue.hpp"

#endif //__PRIORITY_QUEUE_HEADER_INCLUDED__