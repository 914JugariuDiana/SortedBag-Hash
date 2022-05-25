#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <iostream>

int SortedBag::hashFunction(TComp value) const
{
	return abs(value % hashv);
}

SortedBag::SortedBag(Relation r) {
	relation = r;
	hashv = 13;
	alfa = 15;
	hashTable = new HashNode [hashv];
	for (int i = 0; i < hashv; i++)
		hashTable[i].next = nullptr;
	head = nullptr;
	currentSize = 0;
}

void SortedBag::add(TComp e) {
	int hashValue = hashFunction(e);
	Node* node = new Node[1];

	if (currentSize / hashv > alfa)
	{
		hashv = 2 * hashv;
		alfa = 2 * alfa;
		HashNode* nhashTable = new HashNode[hashv];
		for (int i = 0; i < hashv; i++)
			nhashTable[i].next = nullptr;
		Node* n = head->hashNext;
		for (int i = 0; i < currentSize - 1; i++)
		{
			if (nhashTable[hashFunction(n->value)].next == nullptr)
				n->SLLnext = nullptr;
			else
				n->SLLnext = nhashTable[hashFunction(n->value)].next;
			nhashTable[hashFunction(n->value)].next = n;
			n = n->hashNext;
		}

		delete[] hashTable;
		hashTable = nhashTable;
	}
	currentSize += 1;
	node->value = e;
	node->SLLnext = hashTable[hashValue].next;
	hashTable[hashValue].next = node;
	if (head == nullptr)
	{
		node->hashNext = nullptr;
		head = node;
		return;
	}
	Node* orderedHead = head;
	Node* previousNode = nullptr;
	while (orderedHead != nullptr and relation(e, orderedHead->value) != 1)
	{
		previousNode = orderedHead;
		orderedHead = orderedHead->hashNext;
	}
	if (previousNode == nullptr)
	{
		node->hashNext = head;
		head = node;
		return;
	}
	node->hashNext = orderedHead;
	previousNode->hashNext = node;
}


bool SortedBag::remove(TComp e) {
	if (search(e) == 0)
		return false;
	
	int hashValue = hashFunction(e);
	
	Node* previous = nullptr;
	Node* currentPosition = hashTable[hashValue].next;
	while (currentPosition->value != e)
	{
		previous = currentPosition;
		currentPosition = currentPosition->SLLnext;
	}
	
	Node* previousOrdered = nullptr;
	Node* orderedHead = head;
	while (orderedHead->value != e)
	{
		previousOrdered = orderedHead;
		orderedHead = orderedHead->hashNext;
	}

	Node* toRemove = orderedHead;
	if (previous == nullptr)
	{
		hashTable[hashValue].next = hashTable[hashValue].next->SLLnext;
	}
	else
	{
		previous->SLLnext = currentPosition->SLLnext;
	}

	if (previousOrdered == nullptr)
	{
		head = head->hashNext;
	}
	else
	{
		previousOrdered->hashNext = toRemove->hashNext;
	}

	delete toRemove;
	currentSize -= 1;
	return true;
}


bool SortedBag::search(TComp elem) const {
	int hashValue = hashFunction( elem);
	Node* currentPosition = hashTable[hashValue].next;

	while (currentPosition != nullptr and currentPosition->value != elem)
		currentPosition = currentPosition->SLLnext;
	if (currentPosition == nullptr)
		return false;
	return true;
}


int SortedBag::nrOccurrences(TComp elem) const {
	if (search(elem) == 0)
		return 0;

	int count = 0;
	Node* check = hashTable[hashFunction(elem)].next;
	while (check != nullptr)
	{
		if (check->value == elem)
			count += 1;
		check = check->SLLnext;
	}

	return count;
}



int SortedBag::size() const {
	return currentSize;
}


bool SortedBag::isEmpty() const {
	return currentSize == 0;
}


SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}


SortedBag::~SortedBag() {
	Node* toFree = head;
	while (toFree != nullptr)
	{
		head = toFree;
		toFree = toFree->hashNext;
		delete head;
	}
	delete[] hashTable;
}
