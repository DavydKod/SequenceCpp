#include "../../include/Sequence.h"
#include "runTestMethods.h"
#include "cassert"
#include <sstream>
#include <functional>

template <class type, class Func, class... Args>
bool tryCall(Sequence<type>& seq, Func&& func, Args&&... args) {
	try {
		std::invoke(std::forward<Func>(func), seq, std::forward<Args>(args)...);
	}
	catch (std::out_of_range&) {
		return false;
	}
	return true;
}

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

	delete[] elements;
}

void testEmpty() {
	Sequence<int> seq;
	assert(seq.isEmpty());
	seq.push_back(1);
	assert(!seq.isEmpty());
	seq.clear();
	assert(seq.isEmpty());
}

void testPushingPoppingBack() {
	Sequence<int> seq;
	seq.push_back(5).push_back(12).push_back(654).push_back(23);
	assert(seq[0] == 5);
	assert(seq[1] == 12);
	assert(seq[3] == 23);
	seq.pop_back().push_back(234);
	assert(seq[3] == 234);
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

	assert(!tryCall(seq, &Sequence<int>::changeAt, -55, 2));
	assert(!tryCall(seq, &Sequence<int>::changeAt, -65, 2));
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
}

void testPushingOutOfRangeOfCapacity() {
	Sequence<int> seq(2);
	assert(seq.getCapacity() == 2);
	seq.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);
	assert(seq.back() == 234 && seq.getCapacity() == 102);

	Sequence<int> seqA(2);
	assert(seqA.getCapacity() == 2);
	seqA.push_front(5).push_front(12).push_front(654);
	assert(seqA.front() == 654 && seqA.getCapacity() == 102);
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

	assert(!tryCall(seq, &Sequence<int>::insertAt, -57, 58));
	assert(!tryCall(seq, &Sequence<int>::insertAt, 254, 8));
	
	assert(seq.getCapacity() == 110);
	assert(seq.getSize() == 11);
	seq.clear();

	seq.insertAt(0, 66).insertAt(1, 4).insertAt(2, 60);
	assert(seq.getSize() == 3 && seq.at(0) == 66 && seq.at(2) == 60);
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
	
	assert(!tryCall(seq, &Sequence<int>::removeAt, -6));
	assert(!tryCall(seq, &Sequence<int>::removeAt, 87));
	
	seq.removeAll(23).removeAt(0).removeAt(0);
	
	assert(seq.getSize() == 0);
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
}

void testGetting() {
	Sequence<int> seq(6);
	seq.push_back(2).push_back(42).push_back(1).push_back(8);
	assert(seq.at(1) == 42);
	assert(seq.at(3) == 8);
	seq.at(3) = 1;
	assert(seq.at(3) == 1);

	assert(!tryCall(seq, static_cast<int& (Sequence<int>::*)(size_t)>(&Sequence<int>::at), -1));
	assert(!tryCall(seq, static_cast<int& (Sequence<int>::*)(size_t)>(&Sequence<int>::at), 4));
}

template <class type>
Sequence<type> MoveSequenceThroughReturn(Sequence<type>&& seq) {
	return seq;
}

void testMoveSemantics() {
	Sequence<double> seq(new double[] {1,5.6,3}, 3, 10);
	seq = MoveSequenceThroughReturn(std::move(seq));
}

void testPushingArray() {
	Sequence<bool> seq(3);
	seq.push_back(false).push_back(true);
	Sequence<bool> addedSeq;
	addedSeq.push_back(true).push_back(false);

	seq.push_back(addedSeq);
	assert(seq.getCapacity() == 104 && seq.getSize() == 4);
	assert(seq.at(0) == false && seq.at(1) == true && seq.at(2) == true && seq.at(3) == false);

	seq.push_back(new bool[] {true, false, false}, 3);
	assert(seq.getCapacity() == 104 && seq.getSize() == 7);
	assert(seq.at(4) == true && seq.at(5) == false && seq.at(6) == false);
	
	addedSeq.push_back(seq);
	seq.push_back(addedSeq);
	seq.push_back(seq).push_back(seq);
	seq.push_back(seq);
	assert(seq.getSize() == 128 && seq.getCapacity() == 228);
}

void testFrontBack() {
	Sequence<int> seq(10, 25);
	seq.push_back(new int[] {1, 5, 6, 7}, 4);

	assert(seq.front() == 1);
	assert(seq.back() == 7);
	assert(seq.removeAt(0).front() == 5);
	seq.front() = 2;
	seq.back() = 3;
	assert(seq.front() == 2);
	assert(seq.back() == 3);
	const Sequence<int> sequence(new int[] {3}, 1, 2, 10);
	assert(sequence.front() == sequence.back());
}

void testCapacityGrowthStep() {
	Sequence<double> seq(1, 2);
	assert(seq.getCapacityGrowthStep() == 2);
	seq.push_back(2);
	assert(seq.getCapacity() == 1);
	seq.push_front(2);
	assert(seq.getCapacity() == 3);
	seq.setCapacityGrowthStep(5);
	seq.push_back(2).push_back(6);
	assert(seq.getCapacity() == 8);
	seq.setCapacityGrowthStep(0);
	assert(seq.getCapacityGrowthStep() == 1);
}

void testFull() {
	Sequence<double> seq(1, 2);
	seq.push_front(2);
	assert(seq.isFull());
	seq.push_back(2);
	assert(!seq.isFull());
	seq.push_front(3.5);
	assert(seq.isFull());
}

void testFind() {
	const Sequence<int> seq(new int[] {3, 7, 3, 3, 5, 5, 8, 7, 9, 9, 0}, 11, 11, 10);
	assert(seq.find(3) == 0);
	assert(seq.find(5) == 4);
	assert(seq.find(34) == 11);

	assert(seq.findFirst(3) == 0);
	assert(seq.findFirst(5) == 4);
	assert(seq.findFirst(34) == 11);

	assert(seq.findLast(3) == 3);
	assert(seq.findLast(5) == 5);
	assert(seq.findLast(34) == 11);

	assert(seq.findFirst(0) == seq.findLast(0));
}

void testConcatination() {
	Sequence<int> seqA(new int[] {3, 7, 3, 3, 5, 5, 8, 7, 9, 9, 0}, 11, 11, 10);
	const Sequence<int> seqB(new int[] {9, 0}, 2, 11, 10);
	const Sequence<int> seqC;
	seqA.concat(seqB);
	assert(seqA.getSize() == 13);
	assert(seqA.front() == 3 && seqA.back() == 0);
	Sequence<int> seqD = seqA + seqB + seqC + seqA;
	assert(seqD.getSize() == 28);
	seqA += seqD;
	seqD.clear();;
	assert(seqA.getSize() == 41);
	assert(seqA.front() == 3 && seqA.back() == 0);

}

void testPushingAndPoppingFront() {
	Sequence<int> seq(10, 20);
	seq.push_front(45);
	assert(seq.at(0) == 45);
	seq.push_back(4);
	assert(seq.at(0) == 45);
	seq.push_front(0);
	assert(seq.at(0) == 0 && seq.at(1) == 45);
	assert(seq.getSize() == 3);
	seq.pop_front();
	assert(seq.at(0) == 45 && seq.getSize() == 2);
}

void testPushingFrontSequences() {
	Sequence<int> a(new int[]{ 2, 4, 5 }, 3);
	int* b = new int[] {2, 1, 5, 6};
	a.push_front(b, 4);
	assert(a[0] == 2 && a[5] == 4 && a[6] == 5 && a.getSize() == 7);
	a.push_front(a);
	assert(a[0] == 2 && a[13] == 5 && a.getSize() == 14);
	a.push_front(b, 4);
	assert(a[0] == 2 && a[1] == 1 && a[14] == 6 && a[15] == 2 && a[16] == 4 && a[17] == 5 && a.getSize() == 18);

	Sequence<bool> c(new bool[] {false}, 1, 2, 10);
	bool* d = new bool[] {true, false};
	c.push_front(d, 2);
	assert(c[0] == true && c[1] == false && c[2] == false && c.getSize() == 3 && c.getCapacity() == 13);
	c.push_front(Sequence<bool>());
	assert(c[0] == true && c[1] == false && c[2] == false && c.getSize() == 3 && c.getCapacity() == 13);
	delete[] b;
	delete[] d;
}

void testPushingFrontArrays() {
	Sequence<int> a(new int[] { 2, 4, 5 }, 3);
	Sequence<int> b(new int[] { 2, 1, 5, 6 }, 4);
	a.push_front(b);
	assert(a[0] == 2 && a[5] == 4 && a[6] == 5 && a.getSize() == 7);
	a.push_front(a);
	assert(a[0] == 2 && a[13] == 5 && a.getSize() == 14);
	a.push_front(b);
	assert(a[0] == 2 && a[1] == 1 && a[14] == 6 && a[15] == 2 && a[16] == 4 && a[17] == 5 && a.getSize() == 18);
}

void testSizeInBytes() {
	Sequence<int> seq(new int[] { 2, 4, 5, 5, 8 }, 5, 150, 10);
	assert(seq.dataSizeInBytes() == 600 && seq.totalSizeInBytes() == 632);
	seq.reserve(200);
	assert(seq.dataSizeInBytes() == 800 && seq.totalSizeInBytes() == 832);
}

size_t testBasics() {
	runTest(testEmpty);
	runTest(testFull);
	runTest(testPushingPoppingBack);
	runTest(testPrinting);
	runTest(testChanging);
	runTest(testClearing);
	runTest(testPushingOutOfRangeOfCapacity);
	runTest(testContaining);
	runTest(testShrinking);
	runTest(testResizing);
	runTest(testReserving);
	runTest(testRemoving);
	runTest(testInserting);
	runTest(testCopying);
	runTest(testConstObjects);
	runTest(testSwap);
	runTest(testGetting);
	runTest(testMoveSemantics);
	runTest(testPushingArray);
	runTest(testFrontBack);
	runTest(testCapacityGrowthStep);
	runTest(testPushingAndPoppingFront);
	runTest(testFind);
	runTest(testConcatination);
	runTest(testPushingFrontSequences);
	runTest(testPushingFrontArrays);
	runTest(testSizeInBytes);

	return runTest(testCreation);
}