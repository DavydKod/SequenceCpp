#include "test_sequence/test_sequence.h"
#include <iostream>
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define RESET "\033[0m"

void mainTesting() {
	int passedTests = 0;
	passedTests += testSequence();

	std::cerr << MAGENTA << "ALL " << CYAN << passedTests << GREEN << " PASSED" << RESET << std::endl;
}