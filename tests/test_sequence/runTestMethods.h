#ifndef RUN_TEST_METHODS_H
#define RUN_TEST_METHODS_H

template <class Func>
void runTest(Func func, size_t& passedTests) {
	func();
	++passedTests;
}

#endif
