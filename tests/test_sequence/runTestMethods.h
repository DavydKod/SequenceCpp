#ifndef RUN_TEST_METHODS_H
#define RUN_TEST_METHODS_H

template <class Func>
size_t runTest(Func func) {
	static size_t passedTests = 0;
	func();
	return ++passedTests;
}

#endif
