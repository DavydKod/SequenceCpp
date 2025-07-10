#include "../../include/Sequence.h"
#include "cassert"

void testCreation() {
	Sequence<int> seq;
	assert(seq.getCapacity() == 100);
	assert(seq.getSize() == 0);
	Sequence<double> sequence(50);
	assert(sequence.getCapacity() == 50);
	assert(sequence.getSize() == 0);
}

void testEmpty() {
	Sequence<int> seq;
	assert(seq.isEmpty());
	seq.push_back(1);
	assert(!seq.isEmpty());
	seq.clear();
	assert(seq.isEmpty());
}

void testAddingPopping() {
	Sequence<int> seq;
	seq.push_back(5).push_back(12).push_back(654).push_back(23);
	assert(seq[0] == 5);
	assert(seq[1] == 12);
	assert(seq[3] == 23);
	seq.pop_back().push_back(234);
	assert(seq[3] == 234);
	//TODO something is incorrect with insert or remove method
	//seq.push_back(34).insertAt(1, 35).removeAt(3);
	//assert(seq[1] == 35 && seq.getSize() == 4);

}


void test_basics() {
	testCreation();
	testEmpty();
	testAddingPopping();
}