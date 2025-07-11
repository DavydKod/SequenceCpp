int testBasics();
int testOperators();

int testSequence() {
	int passedTests = 0;
	passedTests += testBasics();
	passedTests += testOperators();
	return passedTests;
}