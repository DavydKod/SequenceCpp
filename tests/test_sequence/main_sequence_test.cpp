size_t testBasics();
size_t testOperators();

size_t testSequence() {
	size_t passedTests = 0;
	passedTests += testBasics();
	passedTests += testOperators();
	return passedTests;
}