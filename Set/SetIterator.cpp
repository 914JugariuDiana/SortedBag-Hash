#include "SetIterator.h"
#include "Set.h"
#include <exception>

using namespace std;


SetIterator::SetIterator(const Set& m) : set(m)
{
	//TODO - Implementation
	this->currentPos = 0;
}
//Theta(1)

void SetIterator::first() {
	//TODO - Implementation
	this->currentPos = 0;
}
//Theta(1)

void SetIterator::next() {
	if (this->currentPos >= this->set.currentSize) {
		throw exception();
	}
	else {
		this->currentPos++;
	}
	//TODO - Implementation
}
//Theta(1)

TElem SetIterator::getCurrent()
{
	//TODO - Implementation
	if (this->currentPos >= this->set.currentSize) {
		throw exception();
	}
	else {
		return this->set.elements[this->currentPos];
	}
}
//Theta(1)
bool SetIterator::valid() const {
	//TODO - Implementation
	if (this->currentPos < this->set.currentSize)
		return true;
	return false;
} 
//Theta(1)


