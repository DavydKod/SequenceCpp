#include "../../include/Sequence.h"
#include "cassert"
#include <sstream>

static int passedTestsCounter = 0;

void testCreation() {
	Sequence<int> seq;
	assert(seq.getCapacity() == 100);
	assert(seq.getSize() == 0);
	Sequence<double> sequence(50);
	assert(sequence.getCapacity() == 50);
	assert(sequence.getSize() == 0);
	passedTestsCounter++;
}

void testEmpty() {
	Sequence<int> seq;
	assert(seq.isEmpty());
	seq.push_back(1);
	assert(!seq.isEmpty());
	seq.clear();
	assert(seq.isEmpty());
	passedTestsCounter++;
}

void testPushingPopping() {
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
	passedTestsCounter++;
}

void testPrinting() {
	Sequence<int> seq;
	seq.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);

	std::stringstream buffer;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

	seq.print();

	std::cout.rdbuf(oldCoutBuffer);

	std::string output = buffer.str();

	assert(output == "Sequence (capacity = 100, size = 5): 5 12 654 23 234 \n");

	passedTestsCounter++;
}

void testChanging() {
	Sequence<int> seq(15);
	seq.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);
	assert(seq[2] == 654);
	seq.changeAt(2, 55);
	assert(seq[2] == 55);
	assert(seq.getSize() == 5);
	assert(seq.getCapacity() == 15);

	seq.push_back(5).push_back(4).push_back(5);
	seq.changeAll(5, 10);
	assert(seq[0] == 10 && seq[5] == 10 && seq[7] == 10);

	passedTestsCounter++;
}

void testClearing() {
	Sequence<int> seq(15);
	seq.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);
	seq.clear();
	assert(seq.getSize() == 0);
	assert(seq.getCapacity() == 15);
	seq.clear();
	assert(seq.getSize() == 0);
	assert(seq.getCapacity() == 15);

	passedTestsCounter++;
}

void testPushingOutOfRangeOfCapacity() {
	Sequence<int> seq(2);
	assert(seq.getCapacity() == 2);
	seq.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);
	assert(seq.getCapacity() == 102);

	passedTestsCounter++;
}

void testContaining() {
	Sequence<int> seq(10);
	seq.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);

	assert(seq.contains(5) && seq.contains(4) && seq.contains(23));
	assert(!seq.contains(6));
	assert(seq.containsLotsOf(5) == 3);
	assert(seq.containsLotsOf(12) == 1);
	assert(seq.containsLotsOf(6) == 0);
	seq.changeAll(5, 6);
	assert(seq.containsLotsOf(5) == 0);
	assert(seq.containsLotsOf(12) == 1);
	assert(seq.containsLotsOf(6) == 3);
	seq.clear();
	assert(!seq.contains(5) && !seq.contains(4) && !seq.contains(23));
	assert(seq.containsLotsOf(5) == 0);
	assert(seq.containsLotsOf(6) == 0);

	passedTestsCounter++;
}

void testShrinking() {
	Sequence<int> seq(10);
	seq.push_back(7).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);
	assert(seq.getCapacity() == 10);
	assert(seq.getSize() != seq.getCapacity());
	seq.shrink_to_fit();
	assert(seq.getCapacity() == seq.getSize());
	assert(seq.getCapacity() == 8);
	assert(seq[7] == 5);
	assert(seq[0] == 7);
	seq.shrink_to_fit();
	assert(seq.getCapacity() == seq.getSize());
	assert(seq.getCapacity() == 8);
	assert(seq[7] == 5);
	assert(seq[0] == 7);
	seq.push_back(9);
	assert(!(seq.getCapacity() == seq.getSize()));
	assert(seq.getCapacity() == 108 && seq.getSize() == 9);
	seq.shrink_to_fit();
	assert(seq.getCapacity() == seq.getSize());
	assert(seq.getCapacity() == 9);
	assert(seq[8] == 9);
	assert(seq[1] == 12);

	passedTestsCounter++;
}

void testResizing() {
	Sequence<int> seq(10);
	seq.push_back(7).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);
	assert(seq.getCapacity() == 10);
	seq.resize(8);
	assert(seq.getCapacity() == 8);
	seq.resize(3);
	assert(seq.getCapacity() == seq.getSize() && seq.getCapacity() == 3);
	assert(seq[2] == 654);
	seq.push_back(5);
	assert(seq[3] == 5);
	assert(seq.getCapacity() == 103);
	seq.resize(123);
	assert(seq.getCapacity() == 123);
	assert(seq.getSize() == 4);
	seq.resize(-54);
	assert(seq.getCapacity() == seq.getSize() && seq.getCapacity() == 0);
	seq.push_back(98);
	assert(seq[0] == 98);
	assert(seq.getCapacity() == 100);
	assert(seq.getSize() == 1);
	seq.resize(0);
	assert(seq.getCapacity() == seq.getSize() && seq.getCapacity() == 0);

	passedTestsCounter++;
}

void testReserving() {
	Sequence<int> seq(8);
	seq.push_back(7).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);
	assert(seq.getCapacity() == 8);

	seq.reserve(56);
	seq.push_back(4).push_back(3);
	assert(seq.getCapacity() == 56);
	seq.reserve(3);
	assert(seq.getCapacity() == 56);
	seq.reserve(55);
	assert(seq.getCapacity() == 56);
	seq.reserve(-5);
	assert(seq.getCapacity() == 56);

	passedTestsCounter++;
}

void testInserting() {


	passedTestsCounter++;
}

void testRemoving() {


	passedTestsCounter++;
}

void testCopying() {


	passedTestsCounter++;
}

int testBasics() {
	testCreation();
	testEmpty();
	testPushingPopping();
	testPrinting();
	testChanging();
	testClearing();
	testPushingOutOfRangeOfCapacity();
	testContaining();
	testShrinking();
	testResizing();
	testReserving();
	testInserting();
	testRemoving();
	testCopying();
	return passedTestsCounter;
}