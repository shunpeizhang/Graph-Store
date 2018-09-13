#ifndef __HASH_HEADER_INCLUDED__
#define __HASH_HEADER_INCLUDED__

#include "../Dynamic Array/DynamicArray.h"
#include "Hash Function/HashFunction.h"

class Identity
{
public:
	template <class T>
	const T& operator()(const T& object) const
	{
		return object;
	}
};

template <class Item, class Key = Item, class Function = HashFunction<Key>, class KeyAccessor = Identity>
class Hash
{
	typedef DynamicArray<Item*> Table;

public:
	explicit Hash(size_t expectedItemsCount = 0);
	Hash(const Hash<Item, Key, Function, KeyAccessor>&) = default;
	Hash<Item, Key, Function, KeyAccessor>& operator=(const Hash<Item, Key, Function, KeyAccessor>&) = default;
	Hash(Hash<Item, Key, Function, KeyAccessor>&& source);
	Hash<Item, Key, Function, KeyAccessor>& operator=(Hash<Item, Key, Function, KeyAccessor>&& rhs);
	~Hash() = default;

	void add(Item& item);
	Item* remove(const Key& key);
	bool contains(const Key& key) const;

	Item& operator[](const Key& key);
	const Item& operator[](const Key& key) const;

	size_t getCount() const;
	bool isEmpty() const;
	void empty();

private:
	static Table createEmptyTableWithSize(size_t size);
	static Table emptyAllSlotsIn(Table table);
	static size_t calculateTableSize(size_t expectedItemsCount);

private:
	long getIndexOfFirstItemWithKey(const Key& key) const;
	size_t computeIndexFromKey(const Key& key) const;
	void rehashClusterStartingAt(size_t index);
	Item* emptySlotAndReturnItemAt(size_t index);
	void shrinkAfterRemovingItemAt(size_t index);
	void resize(size_t newSize);
	void addAllItemsFrom(Table& table);
	bool hasTooManyEmptySlots() const;
	bool tableCanBeShrinked() const;
	void extendIfFillingUp();
	bool isFillingUp() const;
	void makeTableEmptyWithSize(size_t size);
	void setTable(Table table);
	void swapContentsWith(Hash<Item, Key, Function, KeyAccessor> hash);
	size_t getNextPositionToProbe(size_t currentPosition) const;
	bool slotIsOccupied(size_t index) const;
	void addItemAt(Item& item, size_t index);

private:
	static const size_t GROWTH_RATE = 2;
	static const size_t MIN_TABLE_SIZE = 3;

private:
	Table table;
	size_t count;
	KeyAccessor keyAccessor;
	Function hashFunction;
};

#include "Hash.hpp"

#endif //__HASH_HEADER_INCLUDED__