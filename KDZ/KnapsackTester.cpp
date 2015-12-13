//
// Created by Computer on 11.12.2015.
//

#include "KnapsackTester.h"
#include <assert.h>

KnapsackTester::KnapsackTester()
{
	vector<Item> *items1 = new vector<Item>();
	items1->push_back(Item(0, 12, 4));
	items1->push_back(Item(1, 2, 2));
	items1->push_back(Item(2, 1, 2));
	items1->push_back(Item(3, 1, 1));
	items1->push_back(Item(4, 4, 10));
	_check_problems.push_back(Problem(5, 5, items1));

	vector<Item> *items2 = new vector<Item>();
	items2->push_back(Item(0, 9, 150));
	items2->push_back(Item(1, 13, 35));
	items2->push_back(Item(2, 153, 200));
	items2->push_back(Item(3, 50, 160));
	items2->push_back(Item(4, 15, 60));
	items2->push_back(Item(5, 68, 45));
	items2->push_back(Item(6, 27, 60));
	items2->push_back(Item(7, 39, 40));
	items2->push_back(Item(8, 23, 30));
	items2->push_back(Item(9, 52, 10));
	items2->push_back(Item(10, 11, 70));
	items2->push_back(Item(11, 32, 30));
	items2->push_back(Item(12, 24, 15));
	items2->push_back(Item(13, 48, 10));
	items2->push_back(Item(14, 73, 40));
	items2->push_back(Item(15, 42, 70));
	items2->push_back(Item(16, 43, 75));
	items2->push_back(Item(17, 22, 80));
	items2->push_back(Item(18, 7, 20));
	items2->push_back(Item(19, 18, 12));
	items2->push_back(Item(20, 4, 50));
	items2->push_back(Item(21, 30, 10));
	_check_problems.push_back(Problem(400, 22, items2));

	_check_costs.push_back(12);
	_check_costs.push_back(1030);
}

KnapsackTester::~KnapsackTester()
{
	for (int i = 0; i < _check_problems.size();i++)
	{
		delete _check_problems[i].items;
	}
}

void KnapsackTester::problemsFromFile() {
	

	vector<Problem> *problems = KnapsackSolver::problemsFromFile("C:\\server\\input_knap_test.txt");
	assert(_check_problems.size() == problems->size());//Wrong number of problems read.");
	for (int i = 0; i < _check_problems.size();i++)
	{
		assert(_check_problems[i].itemsNumber == (*problems)[i].itemsNumber);//Wrong itemsNumber in Problem "+i);
		assert(_check_problems[i].maxWeight == (*problems)[i].maxWeight);//Wrong maxWeight in Problem " + i);
		for (int j = 0; j < _check_problems[i].itemsNumber;j++)
		{
				assert((*_check_problems[i].items)[j] == (*(*problems)[i].items)[j]);//Wrong item in Problem " + j);
		}
	}

}

void KnapsackTester::solve()
{
	KnapsackSolver solver(_check_problems);
	for (int problemNumber = 0; problemNumber < _check_problems.size(); problemNumber++)
	{
		for (int method = 0; method < Method::ALL; method++)
		{
			solver.solve(problemNumber, Method(method),3);
			assert(solver.getSolutions().back().method == Method(method));
			if (Method(method) != Method::GREEDY) {
				assert(solver.getSolutions().back().cost == _check_costs[problemNumber]);
			}
			cout << method << " " << "ok;" << endl;
		}
	}
}

void KnapsackTester::resolveAll()
{
	int times = 3;
	KnapsackSolver solver(_check_problems);
	solver.resolveAll(times);
	for (int problemNumber = 0; problemNumber < _check_problems.size(); problemNumber++)
	{
		for (int method = 0; method < Method::ALL; method++)
		{
			assert(solver.getSolutions()[problemNumber*Method::ALL + method].method == Method(method));
			if (Method(method) != Method::GREEDY) {
				assert(solver.getSolutions()[problemNumber*Method::ALL + method].cost == _check_costs[problemNumber]);
			}
			cout << method << " " << "ok; time: " << solver.getSolutions()[problemNumber*Method::ALL + method].time << endl;
		}
	}
	ofstream outFile("output_knap_test.txt");
	ostream* streams[2];
	streams[0] = &cout;
	streams[1] = &outFile;
	solver.solutionsToStream(streams, 2);
	outFile.close();
}