#include "../../include/Sequence.h"
#include "cassert"

static int passedTestsCounter = 0;

void testIndexOperator() {
	Sequence<int> seq(10);
	seq.push_back(2).push_back(42).push_back(1).push_back(87);
	assert(seq[0] == 2);
	assert(seq[3] == 87);
	seq[2] = 5;
	assert(seq[2] == 5);
	assert(seq.getSize() == 4);

	bool exceptionThrown = false;

	try {
		seq[-1] = 4;
	}
	catch (const std::out_of_range& e) {
		exceptionThrown = true;
	}
	
	assert(exceptionThrown);
	exceptionThrown = false;

	try {
		seq[87] = 4;
	}
	catch (const std::out_of_range& e) {
		exceptionThrown = true;
	}

	assert(exceptionThrown);

	int* elements = new int[] {3, 2, 8, 1};

	const Sequence<int> sequence(elements, 4, 5);
	assert(sequence[0] == 3 && sequence[3] == 1);
	//sequence[2] = 0; - error because of a const object

	assert(exceptionThrown);

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

int testOperators() {
	testIndexOperator();
	testAssignmentOperator();
	return passedTestsCounter;
}