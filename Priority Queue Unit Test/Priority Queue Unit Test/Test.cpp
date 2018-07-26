#include "stdafx.h"
#include "CppUnitTest.h"
#include <utility>
#include "../../Graph Store/Graph Store/PriorityQueue.h"
#include "../../Graph Store/Graph Store/DynamicArray.h"
#include "HandleUpdator.h"
#include "Item.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PriorityQueueUnitTest
{		
	TEST_CLASS(PriorityQueueTest)
	{
		typedef PriorityQueue<Item, unsigned, HandleUpdator> PriorityQueue;
		typedef PriorityQueue::Element<Item, unsigned> Element;

	private:
		static const size_t ARRAY_SIZE = 8;
		static DynamicArray<Item> items;

	private:
		static DynamicArray<Element> createReversedArrayOfElementsFromItems()
		{
			DynamicArray<Element> elements(ARRAY_SIZE);

			for (int i = ARRAY_SIZE - 1; i >= 0; --i)
			{
				elements.add(createElementFromItem(items[i]));
			}

			return elements;
		}

		static bool queueConsistsOfItemsInRange(PriorityQueue& queue,
												unsigned firstNumber,
												unsigned lastNumber)
		{
			assert(isValidRange(firstNumber, lastNumber));
			Element element;

			for (unsigned i = firstNumber; i <= lastNumber; ++i)
			{
				assert(!queue.isEmpty());
				element = queue.extractMinElement();
				
				if (!elementCorrespondsToItem(element, items[i]))
				{
					return false;
				}
			}

			return queue.isEmpty();
		}

		static bool elementCorrespondsToItem(const Element& element, const Item& item)
		{
			return element.item == &item
				   && element.key == item.number;
		}

		static PriorityQueue createQueueFromItemsInRange(unsigned firstNumber,
														 unsigned lastNumber)
		{
			PriorityQueue queue;
			fillQueueWithElementsInRange(queue, firstNumber, lastNumber);

			return queue;
		}

		static void fillQueueWithElementsInRange(PriorityQueue& queue,
												 unsigned firstNumber,
												 unsigned lastNumber)
		{
			assert(isValidRange(firstNumber, lastNumber));

			for (unsigned i = firstNumber; i <= lastNumber; ++i)
			{
				queue.add(createElementFromItem(items[i]));
			}
		}

		static Element createElementFromItem(Item& item)
		{
			return Element(&item, item.number);
		}

		static bool isValidRange(unsigned firstNumber, unsigned lastNumber)
		{
			return firstNumber <= lastNumber && lastNumber < ARRAY_SIZE;
		}

	public:
		TEST_CLASS_INITIALIZE(initialiseItems)
		{
			for (size_t number = 0; number < ARRAY_SIZE; ++number)
			{
				items.add(Item(number));
			}
		}

		TEST_METHOD(testDefaultCtorCreatesAnEmptyQueue)
		{
			PriorityQueue queue;

			Assert::IsTrue(queue.isEmpty());
		}

		TEST_METHOD(testCtorFromIteratorAndCountInsertsFirstCountElements)
		{
			DynamicArray<Element> elements = createReversedArrayOfElementsFromItems();
			DynamicArrayIterator<Element> elementsIterator = elements.getIteratorToFirst();
			size_t numberOfElementsToInsert = elements.getCount();
			
			PriorityQueue queue(elementsIterator, numberOfElementsToInsert);

			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE - 1));
		}

		TEST_METHOD(testCtorFromIteratorAndNullCreatesAnEmptyQueue)
		{
			DynamicArray<Element> elements;
			DynamicArrayIterator<Element> elementsIterator = elements.getIteratorToFirst();

			PriorityQueue queue(elementsIterator, 0);

			Assert::IsTrue(queue.isEmpty());
		}

		TEST_METHOD(testCopyCtorFromEmptyQueue)
		{
			PriorityQueue queueToCopy;
			
			PriorityQueue queue(queueToCopy);

			Assert::IsTrue(queue.isEmpty());
		}

		TEST_METHOD(testCopyCtorFromNonEmptyQueue)
		{
			PriorityQueue queueToCopy = createQueueFromItemsInRange(0, ARRAY_SIZE / 2);

			PriorityQueue queue(queueToCopy);

			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE / 2));
		}

		TEST_METHOD(testCopyAssignmentEmptyToEmptyQueue)
		{
			PriorityQueue queueToCopy;
			PriorityQueue queue;

			queue = queueToCopy;

			Assert::IsTrue(queue.isEmpty());
		}

		TEST_METHOD(testCopyAssignmentEmptyToNonEmptyQueue)
		{
			PriorityQueue queueToCopy;
			PriorityQueue queue = createQueueFromItemsInRange(0, ARRAY_SIZE / 2);

			queue = queueToCopy;

			Assert::IsTrue(queue.isEmpty());
		}

		TEST_METHOD(testCopyAssignmentNonEmptyToEmptyQueue)
		{
			PriorityQueue queueToCopy = createQueueFromItemsInRange(0, ARRAY_SIZE / 2);
			PriorityQueue queue;

			queue = queueToCopy;

			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE / 2));
		}

		TEST_METHOD(testCopyAssignmentNonEmptyToNonEmptyQueue)
		{
			PriorityQueue queueToCopy =
				createQueueFromItemsInRange(0, ARRAY_SIZE / 2);
			PriorityQueue queue =
				createQueueFromItemsInRange((ARRAY_SIZE / 2) + 1, ARRAY_SIZE - 1);

			queue = queueToCopy;

			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE / 2));
		}

		TEST_METHOD(testMoveCtorFromEmptyQueue)
		{
			PriorityQueue queueToMove;

			PriorityQueue queue(std::move(queueToMove));

			Assert::IsTrue(queue.isEmpty());
			Assert::IsTrue(queueToMove.isEmpty(), L"The moved-from queue did not become empty!");
		}

		TEST_METHOD(testMoveCtorFromNonEmptyQueue)
		{
			PriorityQueue queueToMove;
			fillQueueWithElementsInRange(queueToMove, 0, ARRAY_SIZE / 2);

			PriorityQueue queue(std::move(queueToMove));

			Assert::IsTrue(queueToMove.isEmpty(), L"The moved-from queue did not become empty!");
			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE / 2));
		}

		TEST_METHOD(testMoveAssignmentEmptyToEmptyQueue)
		{
			PriorityQueue queueToMove;
			PriorityQueue queue;

			queue = std::move(queueToMove);

			Assert::IsTrue(queue.isEmpty());
			Assert::IsTrue(queueToMove.isEmpty(), L"The moved-from queue did not become empty!");
		}

		TEST_METHOD(testMoveAssignmentEmptyToNonEmptyQueue)
		{
			PriorityQueue queueToMove;
			PriorityQueue queue = createQueueFromItemsInRange(0, ARRAY_SIZE / 2);

			queue = std::move(queueToMove);

			Assert::IsTrue(queue.isEmpty(), L"The moved-into queue did not become empty!");
			Assert::IsTrue(queueToMove.isEmpty());
		}

		TEST_METHOD(testMoveAssignmentNonEmptyToEmpty)
		{
			PriorityQueue queueToMove = createQueueFromItemsInRange(0, ARRAY_SIZE / 2);
			PriorityQueue queue;

			queue = std::move(queueToMove);

			Assert::IsTrue(queueToMove.isEmpty(), L"The moved-from queue did not become empty!");
			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE / 2));
		}

		TEST_METHOD(testMoveAssignmentNonEmptyToNonEmptyQueue)
		{
			PriorityQueue queueToMove =
				createQueueFromItemsInRange(0, ARRAY_SIZE / 2);
			PriorityQueue queue =
				createQueueFromItemsInRange((ARRAY_SIZE / 2) + 1, ARRAY_SIZE - 1);

			queue = std::move(queueToMove);

			Assert::IsTrue(queueToMove.isEmpty(), L"The moved-from queue did not become empty!");
			Assert::IsTrue(queueConsistsOfItemsInRange(queue, 0, ARRAY_SIZE / 2));
		}

	};

	DynamicArray<Item> PriorityQueueTest::items(ARRAY_SIZE);
}