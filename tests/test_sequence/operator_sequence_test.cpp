#include "../../include/Sequence.h"
#include "cassert"

static int passedTestsCounter = 0;

void testIndexOperator() {


	++passedTestsCounter;
}

int testOperators() {
	testIndexOperator();
	return passedTestsCounter;
}