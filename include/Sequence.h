#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <iostream>

template <class type>
class Sequence {
private:
	int size;
	int capacity;
	type* elements = nullptr;
public:
	Sequence(int capacity = 100);
	Sequence(const type* elems, const int size, int capacity = 100);
	Sequence(const Sequence<type>& other);
	~Sequence();

	int getSize() const;
	int getCapacity() const;
	bool isEmpty() const;
	void clear();
	bool contains(const type& value) const;
	size_t containsLotsOf(const type& value) const;
	void resize(int newCapacity);
	void reserve(int newBiggerCapacity);
	void shrink_to_fit();
	Sequence<type>& push_back(const type& value);
	Sequence<type>& pop_back();
	Sequence<type>& insertAt(int index, const type& value);
	Sequence<type>& changeAt(int index, const type& value);
	Sequence<type>& changeAll(const type& previousValue, const type& nextValue);
	Sequence<type>& removeAt(int index);
	Sequence<type>& removeAll(const type& value);
	void print() const;
	void swap(Sequence<type>&);

	type& operator[] (int index);
	const type& operator[] (int index) const;
	Sequence<type>& operator=(const Sequence<type>& other);
	bool operator==(const Sequence<type>&) const;
	bool operator!=(const Sequence<type>&) const;
};


#include "../include/Sequence.h"

template <class type>
Sequence<type>::Sequence(const type* elems, const int size, int capacity) : capacity(capacity) {
	elements = new type[capacity];

	int count = (size < capacity) ? size : capacity;

	for (int i = 0; i < count; ++i) {
		elements[i] = elems[i];
	}

	this->size = count;
}

template <class type>
Sequence<type>::Sequence(int capacity) : capacity(capacity), size(0) {
	elements = new type[capacity];
}

template <class type>
Sequence<type>::~Sequence() {
	delete[] elements;
}

template <class type>
int Sequence<type>::getSize() const {
	return size;
}

template <class type>
int Sequence<type>::getCapacity() const {
	return capacity;
}

template <class type>
type& Sequence<type>::operator[] (int index) {
	if (index >= 0 && index < size) {
		return elements[index];
	}
	throw std::out_of_range("Index " + std::to_string(index) + " out of range " + std::to_string(size));
}

template <class type>
const type& Sequence<type>::operator[] (int index) const {
	if (index >= 0 && index < size) {
		return elements[index];
	}
	throw std::out_of_range("Index " + std::to_string(index) + " out of range " + std::to_string(size));
}

template <class type>
Sequence<type>& Sequence<type>::push_back(const type& value) {
	if (size >= capacity) {
		resize(capacity + 100);
	}
	elements[size] = value;
	++size;
	return *this;
}

template <class type>
bool Sequence<type>::isEmpty() const {
	return size == 0;
}

template <class type>
void Sequence<type>::clear() {
	size = 0;
}

template <class type>
Sequence<type>::Sequence(const Sequence<type>& other) : size(other.size), capacity(other.capacity) {
	elements = new type[capacity];

	for (int i = 0; i < size; i++) {
		elements[i] = other[i];
	}
}

template <class type>
Sequence<type>& Sequence<type>::operator=(const Sequence<type>& other) {
	if (this != &other) {
		delete[] elements;
		capacity = other.getCapacity();
		size = other.getSize();
		elements = new type[capacity];
		for (int i = 0; i < size; i++)
		{
			elements[i] = other[i];
		}
	}
	return *this;
}

template <class type>
bool Sequence<type>::contains(const type& value) const {
	for (int i = 0; i < size; i++)
	{
		if (elements[i] == value) {
			return true;
		}
	}
	return false;
}

template <class type>
size_t Sequence<type>::containsLotsOf(const type& value) const {
	size_t counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (elements[i] == value) {
			counter++;
		}
	}
	return counter;
}

template <class type>
void Sequence<type>::resize(int newCapacity) {
	if (newCapacity < 0)
	{
		clear();
		if (capacity > 0)
		{
			delete[] elements;
		}
		elements = nullptr;
		capacity = 0;
		return;
	}
	if (newCapacity != capacity) {
		type* newElements = new type[newCapacity];
		int newSize = (size > newCapacity) ? newCapacity : size;
		for (int i = 0; i < newSize; i++)
		{
			newElements[i] = elements[i];
		}
		delete[] elements;
		elements = newElements;
		size = newSize;
		capacity = newCapacity;
	}
}

template <class type>
Sequence<type>& Sequence<type>::changeAt(int index, const type& value) {
	if (index < 0)
	{
		index = 0;
	}
	if (index < size)
	{
		elements[index] = value;
	}
	else {
		push_back(value);
	}
	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::removeAt(int index) {
	if (size == 0)
	{
		return *this;
	}

	if (index < 0) {
		index = 0;
	}
	else if (index >= size) {
		index = size - 1;
	}

	for (int i = index; i < size - 1; i++)
	{
		elements[i] = elements[i + 1];
	}
	size--;
	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::insertAt(int index, const type& value) {
	if (size == 0 || index >= size)
	{
		push_back(value);
		return *this;
	}
	if (index < 0) {
		index = 0;
	}
	if (size == capacity)
	{
		resize(capacity + 100);
	}
	size++;

	for (int i = size - 1; i > index; i--)
	{
		elements[i] = elements[i - 1];
	}
	elements[index] = value;

	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::pop_back() {
	if (size > 0)
	{
		size--;
	}
	return *this;
}

template <class type>
void Sequence<type>::reserve(int newBiggerCapacity) {
	if (newBiggerCapacity > capacity)
	{
		resize(newBiggerCapacity);
	}
}

template <class type>
void Sequence<type>::shrink_to_fit() {
	resize(size);
}

template <class type>
Sequence<type>& Sequence<type>::removeAll(const type& value) {
	for (int i = 0; i < size; i++)
	{
		if (elements[i] == value)
		{
			removeAt(i);
			i--;
		}
	}

	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::changeAll(const type& previousValue, const type& nextValue) {
	for (int i = 0; i < size; i++)
	{
		if (elements[i] == previousValue)
		{
			changeAt(i, nextValue);
		}
	}
	return *this;
}

template <class type>
void Sequence<type>::print() const {
	std::cout << "Sequence (capacity = " << capacity << ", size = " << size << "): ";
	for (int i = 0; i < size; i++)
	{
		std::cout << elements[i] << " ";
	}
	std::cout << std::endl;
}

template<class type>
std::ostream& operator<<(std::ostream& os, const Sequence<type>& sequence) {
	os << "Sequence (capacity = " << sequence.getCapacity() << ", size = " << sequence.getSize() << "): ";
	for (int i = 0; i < sequence.getSize(); i++)
	{
		os << sequence[i] << " ";
	}
	os << std::endl;
	
	return os;
}

template<class type>
bool Sequence<type>::operator==(const Sequence<type>& seq) const {
	if (getSize() != seq.getSize())
	{
		return false;
	}
	for (int i = 0; i < getSize(); ++i) {
		if ((*this)[i] != seq[i])
		{
			return false;
		}
	}
	return true;
}

template<class type>
bool Sequence<type>::operator!=(const Sequence<type>& seq) const {
	return !(*this == seq);
}

template <class type>
void Sequence<type>::swap(Sequence<type>& other) {
	int savedSize = getSize();
	size = other.getSize();
	other.size = savedSize;

	int savedCapacity = getCapacity();
	capacity = other.getCapacity();
	other.capacity = savedCapacity;

	type* savedElements = elements;
	elements = other.elements;
	other.elements = savedElements;
}


#endif