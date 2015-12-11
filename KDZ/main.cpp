//
// Коломиец Андрей БПИ143
// CLion 1.1.1 MinGW 3.21
//

#include "KnapsackTester.h"

int main() {
	string a = "test";
	string b = "";
	KnapsackSolver solver(a, b);
	KnapsackTester tester;
	tester.testSolveStatic();
}