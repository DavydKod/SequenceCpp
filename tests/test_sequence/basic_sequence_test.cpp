#include "../../include/Sequence.h"
#include "cassert"
#include <sstream>

static size_t passedTestsCounter = 0;

void testCreation() {
	Sequence<int> seq;
	assert(seq.getCapacity() == 100);
	assert(seq.getSize() == 0);
	Sequence<double> sequence(50);
	assert(sequence.getCapacity() == 50);
	assert(sequence.getSize() == 0);
	int* elements = new int[] {1, 2, 3, 4, 5};
	Sequence<int> s(elements, 5, 8);
	assert(s.getCapacity() == 8 && s.getSize() == 5);
	assert(s[0] == 1 && s[3] == 4);

	bool exceptionThrown = false;
	try {
		Sequence<int> invalidSeq(elements, 5, 2);
	}
	catch (std::invalid_argument&) {
		exceptionThrown = true;
	}
	assert(exceptionThrown);

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

	bool outOfRange = false;
	try {
		seq.changeAt(-55, 2);
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);
	outOfRange = false;

	try {
		seq.changeAt(65, 2);
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);

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
	seq.clear();
	seq.push_back(98);
	assert(seq[0] == 98);
	assert(seq.getCapacity() == 123);
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

	passedTestsCounter++;
}

void testInserting() {
	Sequence<int> seq(10);
	seq.push_back(7).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);
	seq.insertAt(0, 47);
	assert(seq[0] == 47);
	assert(seq[1] == 7);
	assert(seq[2] == 12);
	assert(seq.getSize() == 9);
	assert(seq[8] == 5);
	seq.insertAt(4, 89);
	assert(seq[4] == 89);
	assert(seq[5] == 23);
	seq.insertAt(6, 1);
	assert(seq.getCapacity() == 110);

	bool outOfRange = false;

	try {
		seq.insertAt(-57, 58);
	}
	catch (const std::out_of_range&) {
		assert(seq[0] == 47);
		outOfRange = true;
	}
	assert(outOfRange);
	outOfRange = false;
	
	try {
		seq.insertAt(254, 58);
	}
	catch (const std::out_of_range&) {
		assert(seq[0] == 47);
		outOfRange = true;
	}
	assert(outOfRange);
	outOfRange = false;
	
	assert(seq.getCapacity() == 110);
	assert(seq.getSize() == 11);
	seq.clear();

	try {
		seq.insertAt(0, 58);
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);

	assert(seq.getSize() == 0);

	passedTestsCounter++;
}

void testRemoving() {
	Sequence<int> seq(10);
	seq.push_back(7).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);
	seq.removeAt(0);
	assert(seq[0] == 12);
	assert(seq.getSize() == 7);
	seq.removeAt(4);
	assert(seq[3] == 234);
	assert(seq[4] == 4);
	assert(seq[5] == 5);

	seq.insertAt(2, 5).push_back(5).insertAt(0, 5);
	seq.removeAll(5).removeAll(654).removeAll(2).removeAll(4);
	assert(seq[0] == 12 && seq[1] == 23 && seq[2] == 234 && seq.getSize() == 3);
	
	bool outOfRange = false;
	try {
		seq.removeAt(-6);
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);
	outOfRange = false;
	
	try {
		seq.removeAt(87);
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);
	
	seq.removeAll(23).removeAt(0).removeAt(0);
	
	assert(seq.getSize() == 0);
	passedTestsCounter++;
}

void testCopying() {
	Sequence<int> seq(10);
	seq.push_back(7).push_back(12).push_back(654).push_back(23).push_back(234).push_back(5).push_back(4).push_back(5);

	Sequence<int> sequence(seq);
	assert(sequence[0] == seq[0] && sequence[6] == seq[6] && sequence.getSize() == seq.getSize()
		&& sequence.getCapacity() == seq.getCapacity());
	seq.insertAt(0, 45);
	assert(sequence.getSize() != seq.getSize() && sequence[0] != seq[0] && sequence.getCapacity() == seq.getCapacity());
	sequence.reserve(13);
	assert(sequence.getCapacity() != seq.getCapacity());

	passedTestsCounter++;
}

void testConstObjects() {
	const Sequence<bool> seq(new bool[]{true, false}, 2, 10);
	assert(seq.getCapacity() == 10);
	assert(seq.getSize() == 2);
	assert(seq[0] == true && seq[1] == false);
	assert(seq.at(1) == false);
	assert(!seq.isEmpty());
	assert(seq.contains(true));
	assert(seq.containsLotsOf(false) == 1);

	std::stringstream buffer;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

	seq.print();

	std::cout.rdbuf(oldCoutBuffer);

	std::string output = buffer.str();

	assert(output == "Sequence (capacity = 10, size = 2): 1 0 \n");

	++passedTestsCounter;
}

void testSwap() {
	Sequence<int> seq(10);
	seq.push_back(2).push_back(42).push_back(1).push_back(87);
	Sequence<int> sequence(15);
	sequence.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);

	seq.swap(sequence);

	assert(seq.getSize() == 5 && sequence.getSize() == 4);
	assert(seq.getCapacity() == 15 && sequence.getCapacity() == 10);
	assert(seq[0] == 5 && sequence[2] == 1 && seq[4] == 234);
	
	swap(seq, sequence);

	assert(seq.getSize() == 4 && sequence.getSize() == 5);
	assert(seq.getCapacity() == 10 && sequence.getCapacity() == 15);
	assert(seq[0] == 2 && sequence[2] == 654 && seq[3] == 87);

	++passedTestsCounter;
}

void testGetting() {
	Sequence<int> seq(6);
	seq.push_back(2).push_back(42).push_back(1).push_back(8);
	assert(seq.at(1) == 42);
	assert(seq.at(3) == 8);
	seq.at(3) = 1;
	assert(seq.at(3) == 1);

	bool outOfRange = false;
	try {
		seq.at(-1) = 5;
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);
	outOfRange = false;

	try {
		seq.at(4) = 2;
	}
	catch (const std::out_of_range&) {
		outOfRange = true;
	}
	assert(outOfRange);

	++passedTestsCounter;
}

size_t testBasics() {
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
	testConstObjects();
	testSwap();
	testGetting();
	return passedTestsCounter;
}