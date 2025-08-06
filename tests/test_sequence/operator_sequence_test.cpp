#include "../../include/Sequence.h"
#include "runTestMethods.h"
#include "cassert"
#include <sstream>

void testIndexOperator() {
	Sequence<int> seq(10);
	seq.push_back(2).push_back(42).push_back(1).push_back(87);
	assert(seq[0] == 2);
	assert(seq[3] == 87);
	seq[2] = 5;
	assert(seq[2] == 5);
	assert(seq.getSize() == 4);


	int* elements = new int[] {3, 2, 8, 1};

	const Sequence<int> sequence(elements, 4, 5);
	assert(sequence[0] == 3 && sequence[3] == 1);
}

void testAssignmentOperator() {
	int* elementsA = new int[] {5, 8, 3};
	int* elementsB = new int[] {2, 9, 5};

	Sequence<int> seqA(elementsA, 3, 5);
	Sequence<int> seqB(elementsB, 4, 8);
	Sequence<int> seqC(14);

	seqC = seqA = seqA;
	assert(seqC.getCapacity() == seqA.getCapacity());
	seqA = seqB;
	seqB = seqB;

	assert(seqC[0] == 5 && seqC[2] == 3);
	assert(seqA[0] == 2 && seqA[1] == 9);
	seqA[1] = 5;
	seqC.reserve(20);
	assert(seqB[1] == 9 && seqB[2] == 5);
	assert(seqA.getCapacity() == seqB.getCapacity());
	Sequence<int> seqD;
	seqD = seqA;
	seqC = seqB = seqA;

	assert(seqD.getCapacity() == seqA.getCapacity() && seqD.getCapacity() == seqB.getCapacity()
		&& seqD.getCapacity() == seqC.getCapacity());
	assert(seqA[0] == seqD[0] && seqB[1] == seqD[1] && seqC[2] == seqD[2]);
}

void testOutputOperator() {
	Sequence<int> seq(10);
	seq.push_back(2).push_back(42).push_back(1).push_back(87);

	Sequence<int> sequence(15);
	sequence.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);

	std::stringstream buffer;
	std::streambuf* oldCoutBuffer = std::cout.rdbuf(buffer.rdbuf());

	std::cout << seq << sequence;

	std::cout.rdbuf(oldCoutBuffer);

	std::string output = buffer.str();

	assert(output == "Sequence (capacity = 10, size = 4): 2 42 1 87 \nSequence (capacity = 15, size = 5): 5 12 654 23 234 \n");
}

void testInputOperator() {
	std::stringstream ss("5 10 20 30 40 50");

	Sequence<int> seq(2);
	ss >> seq;

	assert(seq.getCapacity() == 102);
	assert(seq.getSize() == 5);
	assert(seq[0] == 10);
	assert(seq[1] == 20);
	assert(seq[2] == 30);
	assert(seq[3] == 40);
	assert(seq[4] == 50);

	std::stringstream s("5 10 20 40 50");

	Sequence<int> seqA(2);
	s >> seqA;

	assert(seqA.getCapacity() == 102);
	assert(seqA.getSize() == 4);
	assert(seqA[0] == 10);
	assert(seqA[1] == 20);
	assert(seqA[2] == 40);
	assert(seqA[3] == 50);

	std::stringstream is("5 10 20 -40 50 255 6");

	Sequence<int> seqB(2);
	is >> seqB;

	assert(seqB.getCapacity() == 102);
	assert(seqB.getSize() == 5);
	assert(seqB[0] == 10);
	assert(seqB[1] == 20);
	assert(seqB[2] == -40);
	assert(seqB[3] == 50);
	assert(seqB[4] == 255);

	std::stringstream istr("");

	Sequence<int> seqC(2);
	istr >> seqC;

	assert(seqC.getCapacity() == 2);
	assert(seqC.getSize() == 0);

	std::stringstream sstream("abc");
	Sequence<int> seqD;
	sstream >> seqD;
	assert(seqD.getSize() == 0);
	assert(sstream.fail());

	std::stringstream stream("4 -6 abc -2");
	Sequence<int> seqE;
	stream >> seqE;
	assert(seqE.getSize() == 1);
	assert(seqE.at(0) == -6);
	assert(stream.fail());
}

void testComparisonOperator() {
	Sequence<int> seq(10);
	seq.push_back(2).push_back(42).push_back(1).push_back(87);
	Sequence<int> sequence(15);
	sequence.push_back(5).push_back(12).push_back(654).push_back(23).push_back(234);

	assert(seq != sequence);
	assert(!(seq == sequence));

	seq = sequence;
	assert(seq == sequence);
	assert(!(seq != sequence));

	seq.clear();

	assert(seq != sequence);
	assert(!(seq == sequence));

	sequence.clear();

	assert(seq == sequence);
	assert(!(seq != sequence));
}

size_t testOperators() {
	runTest(testAssignmentOperator);
	runTest(testOutputOperator);
	runTest(testInputOperator);
	runTest(testComparisonOperator);
	return runTest(testIndexOperator);
}