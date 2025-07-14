#include "../../include/Sequence.h"
#include "cassert"
#include <sstream>

static size_t passedTestsCounter = 0;

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

	++passedTestsCounter;
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

	++passedTestsCounter;
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

	++passedTestsCounter;
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

	++passedTestsCounter;
}

size_t testOperators() {
	testIndexOperator();
	testAssignmentOperator();
	testOutputOperator();
	testComparisonOperator();
	return passedTestsCounter;
}