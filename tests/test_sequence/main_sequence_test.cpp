size_t testBasics();
size_t testOperators();


size_t testSequence() {
	testBasics();
	return testOperators();
}