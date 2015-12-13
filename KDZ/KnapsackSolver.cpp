//
// Created by Computer on 06.12.2015.
//

#include <iostream>
#include "KnapsackSolver.h"
#ifdef _MSC_VER
#include <intrin.h>
#else
#include <x86intrin.h>
#endif
#include <stdexcept>
#include<algorithm>

void KnapsackSolver::solveIterative() {
    if (_currentProblem >= _problems.size()) {
        /*
		throw length_error("No problem to solve.\n");
		*/
		_currentProblem = 0;
    }
    // Setting time
    uint64_t t = __rdtsc();

    Problem problem = _problems[_currentProblem];
    // Temp arrays
    vector<int> bestKnapsack(problem.itemsNumber);
    int bestCost = 0;
    int bestSize = 0;
    vector<Item> *knapsack = new vector<Item>();
    knapsack->reserve(problem.itemsNumber);
    int knapsackWeight = 0;
    int knapsackCost = 0;
    int currentItem = 0;

    // Algorithm
    while (currentItem < problem.itemsNumber || !knapsack->empty()) {
        // Trying to add items
        for (int i = currentItem; i < problem.itemsNumber; i++) {
            Item item = (*problem.items)[i];
            if (knapsackWeight + item.weight > problem.maxWeight) {
                // Does not fit
                continue;
            }
            // Fits
            knapsack->push_back(item);
            knapsackWeight += item.weight;
            knapsackCost += item.cost;
        }

        // Checking if current knapsack is better than previous ones
        if (knapsackCost > bestCost) {
            bestCost = knapsackCost;
            bestSize = knapsack->size();
            for (int i = 0; i < bestSize; i++) {
                bestKnapsack[i] = (*knapsack)[i].number;
            }

        }

        // Stepping back
        knapsackWeight -= knapsack->back().weight;
        knapsackCost -= knapsack->back().cost;
        currentItem = knapsack->back().number + 1;
        knapsack->pop_back();
    }

    // Preparing the answer
    int bestWeight = 0;
    knapsack->resize(bestSize);
    for (int i = 0; i < bestSize; i++) {
        (*knapsack)[i] = (*problem.items)[bestKnapsack[i]];
        bestWeight += (*knapsack)[i].weight;
    }
    _solutions.push_back(Solution(bestWeight, bestCost, bestSize, knapsack, ITERATIVE,
                                 __rdtsc() - t));
}


void KnapsackSolver::_solveRecursive_grain(int currentItem) {
    for (int i = currentItem; i < _problems[_currentProblem].itemsNumber; i++) {
        Item item = (*_problems[_currentProblem].items)[i];
        if (_solveRecursive_knapsackWeight + item.weight > _problems[_currentProblem].maxWeight) {
            // Does not fit
            continue;
        }
        // Fits
        _solveRecursive_knapsack->push_back(item);
        _solveRecursive_knapsackWeight += item.weight;
        _solveRecursive_knapsackCost += item.cost;
    }

    // Checking if current knapsack is better than previous ones
    if (_solveRecursive_knapsackCost > _solveRecursive_bestCost) {
        _solveRecursive_bestCost = _solveRecursive_knapsackCost;
        _solveRecursive_bestSize = _solveRecursive_knapsack->size();
        for (int i = 0; i < _solveRecursive_bestSize; i++) {
            (*_solveRecursive_bestKnapsack)[i] = (*_solveRecursive_knapsack)[i].number;
        }
    }
    _solveRecursive_knapsackWeight -= _solveRecursive_knapsack->back().weight;
    _solveRecursive_knapsackCost -= _solveRecursive_knapsack->back().cost;
    currentItem = _solveRecursive_knapsack->back().number + 1;
    _solveRecursive_knapsack->pop_back();
    if (currentItem >= _problems[_currentProblem].itemsNumber && _solveRecursive_knapsack->empty()) {
        return;
    }
    _solveRecursive_grain(currentItem);
}

void KnapsackSolver::solveRecursive() {
    if (_currentProblem >= _problems.size()) {
		/*
		throw length_error("No problem to solve.\n");
		*/
		_currentProblem = 0;
    }
    uint64_t t = __rdtsc();

    _solveRecursive_bestCost = 0;
    _solveRecursive_bestSize = 0;
    _solveRecursive_knapsackWeight = 0;
    _solveRecursive_knapsackCost = 0;
    _solveRecursive_knapsack = new vector<Item>();
    _solveRecursive_knapsack->reserve(_problems[_currentProblem].itemsNumber);
    _solveRecursive_bestKnapsack = new vector<int>(_problems[_currentProblem].itemsNumber);
    _solveRecursive_grain(0);

    int bestWeight = 0;
    _solveRecursive_knapsack->resize(_solveRecursive_bestSize);
    for (int i = 0; i < _solveRecursive_bestSize; i++) {
        (*_solveRecursive_knapsack)[i] = (*_problems[_currentProblem].items)[(*_solveRecursive_bestKnapsack)[i]];
        bestWeight += (*_solveRecursive_knapsack)[i].weight;
    }
	_solutions.push_back(Solution(bestWeight, _solveRecursive_bestCost, _solveRecursive_bestSize,
                                 new vector<Item>(*_solveRecursive_knapsack), RECURSIVE,
                                 __rdtsc() - t));
    delete _solveRecursive_bestKnapsack;
    delete _solveRecursive_knapsack;
}

void KnapsackSolver::_solveDynamic_grain(int n, int m) {
    if (_solveDynamic_matrix[n][m] == 0) {
        return;
    }
    if (n > 0 && _solveDynamic_matrix[n - 1][m] == _solveDynamic_matrix[n][m]) {
        _solveDynamic_grain(n - 1, m);
    }
    else {
		if ((m - (*_solveDynamic_items)[n].weight)>=0) {
			_solveDynamic_grain(max(0,n - 1), m - (*_solveDynamic_items)[n].weight);
		}
        _solveDynamic_knapsack->push_back((*_solveDynamic_items)[n]);
    }
}

void KnapsackSolver::solveDynamic() {
    if (_currentProblem >= _problems.size()) {
		/*
		throw length_error("No problem to solve.\n");
		*/
		_currentProblem = 0;
    }
    // Setting time
    uint64_t t = __rdtsc();

    Problem problem = _problems[_currentProblem];
    int n = problem.itemsNumber;
    int m = problem.maxWeight;
    _solveDynamic_matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        _solveDynamic_matrix[i] = new int[m];
    }
    for (int i = 0; i < m; i++) {
        _solveDynamic_matrix[0][i] = (*problem.items)[0].weight > i + 1 ? 0 : (*problem.items)[0].cost;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < m; j++) {
			int w = (*problem.items)[i].weight;
			_solveDynamic_matrix[i][j] = w > j + 1 ?
				_solveDynamic_matrix[i - 1][j] :
				max(_solveDynamic_matrix[i - 1][j], (j - w < 0 ? 0 : _solveDynamic_matrix[i - 1][j - w]) + (*problem.items)[i].cost);
        }
    }

    _solveDynamic_items = problem.items;
    _solveDynamic_knapsack = new vector<Item>();
    _solveDynamic_grain(n - 1, m - 1);

    int bestWeight = 0;
    int bestCost = 0;
    int bestSize = _solveDynamic_knapsack->size();
    for (int i = 0; i < bestSize; i++) {
        bestWeight += (*_solveDynamic_knapsack)[i].weight;
        bestCost += (*_solveDynamic_knapsack)[i].cost;
    }

	_solutions.push_back(Solution(bestWeight, bestCost, bestSize, _solveDynamic_knapsack, DYNAMIC,
                                 __rdtsc() - t));
    delete[] _solveDynamic_matrix;
}

void KnapsackSolver::solveGreedy() {
	if (_currentProblem >= _problems.size()) {
		/*
		throw length_error("No problem to solve.\n");
		*/
		_currentProblem = 0;
	}
	// Setting time
	uint64_t t = __rdtsc();

	Problem problem = _problems[_currentProblem];
	vector<Item> sorted(*problem.items);

	sort(sorted.begin(),sorted.end(),[](Item q1, Item q2)
	{
		return double(q1.weight) / q1.cost < double(q2.weight) / q2.cost;
	});
	vector<Item> *knapsack = new vector<Item>();
	int w = problem.maxWeight;
	int i = 0;
	int bestCost = 0;
	while (w>0 && i<problem.itemsNumber)
	{
		if (w>=sorted[i].weight)
		{
			knapsack->push_back(sorted[i]);

			w -=sorted[i].weight;
			bestCost += sorted[i].cost;
		}
		i++;
	}
	uint64_t ti = __rdtsc();
	_solutions.push_back(Solution(problem.maxWeight - w, bestCost, knapsack->size(), knapsack, GREEDY, ti - t));
}

void KnapsackSolver::destroySolutions()
{
	for (int i = 0; i < _solutions.size();i++)
	{
		delete _solutions[i].items;
	}
	_solutions.clear();
}


KnapsackSolver::KnapsackSolver(vector<Problem> problems) : _numberOfTests(problems.size()), _problems(problems), _currentProblem(0) {
    if (problems.empty()) {
		/*
        throw length_error("Passed empty problems set.");
		*/
    }
}

vector<KnapsackSolver::Problem> *KnapsackSolver::problemsFromFile(string inputPath) {
    ifstream inputStream(inputPath);
    int numberOfTests;
    inputStream >> numberOfTests;
    if (numberOfTests < 1) {
        inputStream.close();
		/*
        throw length_error("Passed empty problems set.");
		*/
    }
    vector<Problem> *problems = new vector<Problem>();
    problems->reserve(numberOfTests);

    for (int testNumber = 0; testNumber < numberOfTests; testNumber++) {
        int maxWeight;
        inputStream >> maxWeight;
        int itemsNumber;
        inputStream >> itemsNumber;
        int *itemsWeights = new int[itemsNumber];
        for (int i = 0; i < itemsNumber; i++) {
            inputStream >> itemsWeights[i];
        }
        vector<Item> *items = new vector<Item>();
        items->reserve(itemsNumber);
        int itemCost;
        for (int i = 0; i < itemsNumber; i++) {
            inputStream >> itemCost;
            items->push_back(Item(i, itemsWeights[i], itemCost));
        }
        delete[] itemsWeights;
        problems->push_back(Problem(maxWeight, itemsNumber, items));
    }
    inputStream.close();
    return problems;
}

void KnapsackSolver::solutionsToStream(ostream** streams,int streamNumber)
{
	for (int solutionNumber = 0; solutionNumber < _solutions.size();solutionNumber++)
	{
		Solution solution = _solutions[solutionNumber];
		for (int s = 0; s < streamNumber;s++)
		{
			(*streams[s]) << (solutionNumber + 1) << endl;
			(*streams[s]) << solution.method << endl;
			(*streams[s]) << solution.time << " cycles average" << endl;
			(*streams[s]) << solution.weight << endl;
			(*streams[s]) << solution.cost << endl;
			for (int itemNumber = 0; itemNumber < solution.itemsNumber-1;itemNumber++)
			{
				(*streams[s]) << (*solution.items)[itemNumber].number << " ";
			}
			(*streams[s]) << (*solution.items)[solution.itemsNumber-1].number << endl;
			for (int itemNumber = 0; itemNumber < solution.itemsNumber - 1; itemNumber++)
			{
				(*streams[s]) << (*solution.items)[itemNumber].weight << " ";
			}
			(*streams[s]) << (*solution.items)[solution.itemsNumber-1].weight << endl;
			for (int itemNumber = 0; itemNumber < solution.itemsNumber - 1; itemNumber++)
			{
				(*streams[s]) << (*solution.items)[itemNumber].cost << " ";
			}
			(*streams[s]) << (*solution.items)[solution.itemsNumber-1].cost << endl;
		}
	}
}

void KnapsackSolver::solve(int problemNumber, Method method, int times) {
    _currentProblem = problemNumber;
    int solutionNumber = _solutions.size();
    for (int i = 0;i<times;i++) {
        switch (method) {
            case ITERATIVE:
                solveIterative();
                break;
            case RECURSIVE:
                solveRecursive();
                break;
            case DYNAMIC:
                solveDynamic();
                break;
            case GREEDY:
                solveGreedy();
                break;
            case ALL:
                solveIterative();
                solveRecursive();
                solveDynamic();
                solveGreedy();
            default:
                break;
        }
        if (i>0){
            _solutions[solutionNumber].time = (_solutions[solutionNumber].time*i + _solutions.back().time)/double(i) - _solutions[solutionNumber].time;
			_solutions.pop_back();
        }
    }
}

void KnapsackSolver::resolveAll(int times) {
	destroySolutions();
    for (int testNumber = 0; testNumber < _numberOfTests; testNumber++) {
        for (int currentMethod = 0; currentMethod < ALL; currentMethod++) {
            solve(testNumber, Method(currentMethod),times);
        }
    }
}

KnapsackSolver::~KnapsackSolver() {
	destroySolutions();
	for (int i = 0; i < _problems.size();i++)
	{
		delete _problems[i].items;
	}
}

KnapsackSolver::Item::Item(int number, int weight, int cost) : number(number), weight(weight), cost(cost) { }

KnapsackSolver::Problem::Problem(int maxWeight, int itemsNumber, vector<Item> *items)
        : maxWeight(maxWeight), itemsNumber(itemsNumber),
          items(items) { }

KnapsackSolver::Solution::Solution(int weight, int cost, int itemsNumber, vector<Item> *items, Method method,
                                   int64_t time)
        : weight(weight), cost(cost), itemsNumber(itemsNumber), items(items), method(method), time(time) { }

bool operator==(const KnapsackSolver::Item& lhs, const KnapsackSolver::Item& rhs) {
    return lhs.number == rhs.number
           && lhs.weight == rhs.weight
           && lhs.cost == rhs.cost;
}

bool operator!=(const KnapsackSolver::Item& lhs, const KnapsackSolver::Item& rhs) {
    return !(lhs == rhs);
}

int KnapsackSolver::getNumberOfTests() const {
    return _numberOfTests;
}

vector<KnapsackSolver::Problem> KnapsackSolver::getProblems() const {
    return _problems;
}

vector<KnapsackSolver::Solution> KnapsackSolver::getSolutions() const {
    return _solutions;
}

string KnapsackSolver::methodToString(Method method) {
    switch (method){
        case ITERATIVE: return "Iterative";
        case RECURSIVE: return "Recursive";
        case DYNAMIC: return "Dynamic";
        case GREEDY: return "Greedy";
        case ALL: return "All";
        default: return "N/A";
    }
}