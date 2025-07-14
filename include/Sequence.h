#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <string>
#include <iostream>

template <class type>
class Sequence {
private:
	size_t size;
	size_t capacity;
	type* elements = nullptr;
public:
	Sequence(size_t capacity = 100);
	Sequence(const type* elems, const size_t size, size_t capacity = 100);
	Sequence(const Sequence<type>&);
	Sequence(Sequence&&) noexcept;
	~Sequence() noexcept;

	[[nodiscard]] size_t getSize() const noexcept;
	[[nodiscard]] size_t getCapacity() const noexcept;
	[[nodiscard]] bool isEmpty() const noexcept;
	void clear() noexcept;
	[[nodiscard]] bool contains(const type&) const noexcept(noexcept(std::declval<type>() == std::declval<type>()));
	[[nodiscard]] size_t containsLotsOf(const type&) const noexcept(noexcept(std::declval<type>() == std::declval<type>()));
	void resize(size_t newCapacity);
	void reserve(size_t newBiggerCapacity);
	void shrink_to_fit();
	Sequence<type>& push_back(const type&);
	Sequence<type>& pop_back() noexcept;
	Sequence<type>& insertAt(size_t index, const type& value);
	Sequence<type>& changeAt(size_t index, const type& value);
	Sequence<type>& changeAll(const type& previousValue, const type& nextValue);
	Sequence<type>& removeAt(size_t);
	Sequence<type>& removeAll(const type&);
	[[nodiscard]] type& at(size_t);
	[[nodiscard]] const type& at(size_t) const;
	void print() const;
	void swap(Sequence<type>&) noexcept;

	[[nodiscard]] type& operator[] (size_t);
	[[nodiscard]] const type& operator[] (size_t) const;
	Sequence<type>& operator=(const Sequence<type>&);
	Sequence<type>& operator=(Sequence<type>&&) noexcept;
	[[nodiscard]] bool operator==(const Sequence<type>&) const noexcept(noexcept(std::declval<type>() == std::declval<type>()));
	[[nodiscard]] bool operator!=(const Sequence<type>&) const noexcept(noexcept(std::declval<type>() == std::declval<type>()));
};

template <class type>
Sequence<type>::Sequence(const type* elems, const size_t size, size_t capacity) : size(size), capacity(capacity) {
	if (size > capacity) {
		throw std::invalid_argument("Sequence constructor: size cannot be greater than capacity");
	}

	elements = new type[capacity];

	for (size_t i = 0; i < size; ++i) {
		elements[i] = elems[i];
	}
}

template <class type>
Sequence<type>::Sequence(size_t capacity) : capacity(capacity), size(0) {
	elements = new type[capacity];
}

template <class type>
Sequence<type>::~Sequence() noexcept {
	delete[] elements;
}

template <class type>
size_t Sequence<type>::getSize() const noexcept {
	return size;
}

template <class type>
size_t Sequence<type>::getCapacity() const noexcept {
	return capacity;
}

template <class type>
type& Sequence<type>::operator[] (size_t index) {
	return elements[index];
}

template <class type>
const type& Sequence<type>::operator[] (size_t index) const {
	return elements[index];
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
bool Sequence<type>::isEmpty() const noexcept {
	return size == 0;
}

template <class type>
void Sequence<type>::clear() noexcept {
	size = 0;
}

template <class type>
Sequence<type>::Sequence(const Sequence<type>& other) : size(other.size), capacity(other.capacity) {
	elements = new type[capacity];

	for (size_t i = 0; i < size; i++) {
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
		for (size_t i = 0; i < size; i++)
		{
			elements[i] = other[i];
		}
	}
	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::operator=(Sequence<type>&& other) noexcept {
	if (this != &other) {
		delete[] elements;
		
		elements = other.elements;
		size = other.size;
		capacity = other.capacity;

		other.elements = nullptr;
		other.size = 0;
		other.capacity = 0;
	}
	return *this;
}

template <class type>
bool Sequence<type>::contains(const type& value) const noexcept(noexcept(std::declval<type>() == std::declval<type>())) {
	for (size_t i = 0; i < size; i++)
	{
		if (elements[i] == value) {
			return true;
		}
	}
	return false;
}

template <class type>
size_t Sequence<type>::containsLotsOf(const type& value) const noexcept(noexcept(std::declval<type>() == std::declval<type>())) {
	size_t counter = 0;
	for (size_t i = 0; i < size; i++)
	{
		if (elements[i] == value) {
			counter++;
		}
	}
	return counter;
}

template <class type>
void Sequence<type>::resize(size_t newCapacity) {
	if (newCapacity != capacity) {
		type* newElements = new type[newCapacity];
		size_t newSize = (size > newCapacity) ? newCapacity : size;
		for (size_t i = 0; i < newSize; i++)
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
Sequence<type>& Sequence<type>::changeAt(size_t index, const type& value) {
	if (index >= size)
	{
		throw std::out_of_range("Index out of range");
	}

	elements[index] = value;

	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::removeAt(size_t index) {
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}

	for (size_t i = index; i < size - 1; i++)
	{
		elements[i] = elements[i + 1];
	}
	size--;
	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::insertAt(size_t index, const type& value) {
	if (index > size) {
		throw std::out_of_range("Index out of range");
	}

	if (size == capacity)
	{
		resize(capacity + 100);
	}
	size++;

	for (size_t i = size - 1; i > index; i--)
	{
		elements[i] = elements[i - 1];
	}
	elements[index] = value;

	return *this;
}

template <class type>
Sequence<type>& Sequence<type>::pop_back() noexcept {
	if (size > 0)
	{
		size--;
	}
	return *this;
}

template<class type>
type& Sequence<type>::at(size_t index) {
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}

	return elements[index];
}
template<class type>
const type& Sequence<type>::at(size_t index) const {
	if (index >= size) {
		throw std::out_of_range("Index out of range");
	}

	return elements[index];
}

template <class type>
void Sequence<type>::reserve(size_t newBiggerCapacity) {
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
	for (size_t i = 0; i < size; i++)
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
	for (size_t i = 0; i < size; i++)
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
	for (size_t i = 0; i < size; i++)
	{
		std::cout << elements[i] << " ";
	}
	std::cout << std::endl;
}

template<class type>
std::ostream& operator<<(std::ostream& os, const Sequence<type>& sequence) {
	os << "Sequence (capacity = " << sequence.getCapacity() << ", size = " << sequence.getSize() << "): ";
	for (size_t i = 0; i < sequence.getSize(); i++)
	{
		os << sequence[i] << " ";
	}
	os << std::endl;
	
	return os;
}

template<class type>
std::istream& operator>>(std::istream& is, Sequence<type>& seq) {
	size_t n;
	is >> n; 
	if (!is) return is;

	seq.clear();

	for (size_t i = 0; i < n; ++i) {
		type value;
		is >> value;
		if (!is) break;

		seq.push_back(value);
	}

	return is;
}

template<class type>
bool Sequence<type>::operator==(const Sequence<type>& seq) const noexcept(noexcept(std::declval<type>() == std::declval<type>())) {
	if (getSize() != seq.getSize())
	{
		return false;
	}
	for (size_t i = 0; i < getSize(); ++i) {
		if ((*this)[i] != seq[i])
		{
			return false;
		}
	}
	return true;
}

template<class type>
bool Sequence<type>::operator!=(const Sequence<type>& seq) const noexcept(noexcept(std::declval<type>() == std::declval<type>())) {
	return !(*this == seq);
}

template <class type>
void Sequence<type>::swap(Sequence<type>& other) noexcept {
	size_t savedSize = getSize();
	size = other.getSize();
	other.size = savedSize;

	size_t savedCapacity = getCapacity();
	capacity = other.getCapacity();
	other.capacity = savedCapacity;

	type* savedElements = elements;
	elements = other.elements;
	other.elements = savedElements;
}

template <class type>
void swap(Sequence<type>& a, Sequence<type>& b) noexcept {
	a.swap(b);
}

template<class type>
Sequence<type>::Sequence(Sequence&& other) noexcept: elements(other.elements), size(other.size), capacity(other.capacity) {
	other.elements = nullptr;
	other.size = 0;
	other.capacity = 0;
}

#endif