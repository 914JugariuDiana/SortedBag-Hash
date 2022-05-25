#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	currentPosition = b.head;
	pos = 0;
}

TComp SortedBagIterator::getCurrent() {
	if (currentPosition == nullptr)
		throw exception();

	return currentPosition->value;
}

bool SortedBagIterator::valid() {
	if (currentPosition == nullptr)
		return false;
	return true;
}

void SortedBagIterator::next() {
	if (currentPosition == nullptr)
		throw exception();
	pos++;
	currentPosition = currentPosition->hashNext;
}

void SortedBagIterator::first() {
	currentPosition = bag.head;
}

void SortedBagIterator::previous()
{
	if (currentPosition == bag.head->hashNext)
		throw exception();

	int i = 2;
	SortedBag::Node* node = bag.head->hashNext;
	while (i < pos)
	{
		node = node->hashNext;
		i++;
	}
	pos--;
	currentPosition = node;
}

