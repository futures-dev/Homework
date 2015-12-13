//
// Коломиец Андрей БПИ143
// CLion 1.1.1 MinGW 3.21
//


#include <stdlib.h>
#include "KnapsackTester.h"

int main(int argc, char* argv[]) {
	/*
	 * KDZ.exe [inputPath] [outputPath] [times]
	 * For next argument, previous are needed.
	 */
	string inputPath = "input_knap.txt";
	string outputPath = "output_knap.txt";
	int times = 20;
	switch (argc)
	{
		case 4:
			times = atoi(argv[3]);
		case 3:
			outputPath = string(argv[2]);
		case 2:
			inputPath = string(argv[1]);
		default:break;
	}
	cout << "0/1 Knapsack problem solver." << endl;
	cout << "Output format: " << endl;
	cout << "Test number" << endl;
	cout << "Algorithm name" << endl;
	cout << "Knapsack weight" << endl;
	cout << "Knapsack cost" << endl;
	cout << "Items number" << endl;
	cout << "Items indices" << endl;
	cout << "Items weights" << endl;
	cout << "Items costs" << endl;
	cout << "-----------------------" << endl;
	cout << "Reading input file..." << endl;
	/*
	string b = "";
	KnapsackTester tester;
	tester.solve();
	tester.problemsFromFile();
	tester.resolveAll();
	cin >> b;
	*/
	vector<Problem> problems = *KnapsackSolver::problemsFromFile(inputPath);
	KnapsackSolver solver(problems);
	cout << "Read " << solver.getNumberOfTests() << " problems." << endl;
	cout << "Solving... (may take up to several minutes on big inputs)" << endl;
	solver.resolveAll(times);
	cout << "Solved!" << endl;
	ofstream outFile(outputPath);
	ostream* streams[2];
	streams[0] = &cout;
	streams[1] = &outFile;
	solver.solutionsToStream(streams, 2);
	cout << "-----------------------" << endl;
	cout << "Press Enter to exit..." << endl;
	cin.get();
}