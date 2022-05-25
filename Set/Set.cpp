#include "Set.h"
#include "SetITerator.h"
#include <exception>

using namespace std;

Set::Set() {
	this->capacity = 100;
	this->currentSize = 0;
	this->elements = new TElem[this->capacity];
}
//Theta(1)

bool Set::add(TElem elem) {
	if (this->capacity == this->currentSize + 1){
		this->capacity *= 2;
		TElem* resize_arr = new TElem[this->capacity];
		if (resize_arr == NULL) {
			this->capacity /= 2;
			return false;
		}
		for (int i = 0; i < this->currentSize; i++)
		{
			resize_arr[i] = this->elements[i];

		}
		delete[] this->elements;
		this->elements = resize_arr;
	}
	int index = 0;
	while (index < this->currentSize and this->elements[index] != elem)
		index++;

	if (index < this->currentSize)
		return false;
	else {
		this->elements[this->currentSize++] = elem;
		return true;
	}
}
//Best case-Theta(1), Worst case - Theta(number of elements) Total O(num of elem)

bool Set::remove(TElem elem) {
	int index = 0;
	while (index < this->currentSize and elements[index] != elem)
		index++;

	if (index < this->currentSize) {
		this->elements[index] = this->elements[currentSize - 1];
		this->currentSize--;
		return true;
	}
	return false;
}
//Best case-Theta(1), Worst case -Theta(number of elements) Total O(num of elem)
bool Set::search(TElem elem) const {
	int index = 0;
	while (index < this->currentSize and elements[index] != elem)
		index++;

	if (index < this->currentSize)
		return true;

	return false;
}
//Best case-Theta(1), Worst case -Theta(number of elements) Total O(num of elem)

int Set::size() const {
	return this->currentSize;
}
//Theta(1)

bool Set::isEmpty() const {
	if (this->currentSize == 0)
		return true;
	return false;
}
//Theta(1)

Set::~Set() {
	delete[] this->elements;
}
//Theta(1) 

SetIterator Set::iterator() const {
	return SetIterator(*this);
}
//Theta(1)

