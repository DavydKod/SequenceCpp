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
	Sequence<type>& removeAt(int index);
	Sequence<type>& removeAll(const type& value);
	Sequence<type>& changeAll(const type& previousValue, const type& nextValue);
	void print() const;

	type& operator[] (int index);
	Sequence<type>& operator=(const Sequence<type>& other);
	const type& operator[] (int index) const;
};

#endif