//
// Created by Computer on 06.12.2015.
//

#include <iostream>
#include "KnapsackSolver.h"
#include <x86intrin.h>
#include <stdexcept>

KnapsackSolver::Solution KnapsackSolver::solveIterative() {
    if (_currentProblem >= _problems.size()) {
        throw length_error("No problem to solve.\n");
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
    Solution solution = Solution(bestWeight, bestCost, bestSize, knapsack, ITERATIVE,
                                 (__rdtsc() - t) / CLOCKS_PER_NANOSECOND);

    return solution;
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

KnapsackSolver::Solution KnapsackSolver::solveRecursive() {
    if (_currentProblem >= _problems.size()) {
        throw length_error("No problem to solve.\n");
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
    Solution solution = Solution(bestWeight, _solveRecursive_bestCost, _solveRecursive_bestSize,
                                 new vector<Item>(*_solveRecursive_knapsack), RECURSIVE,
                                 (__rdtsc() - t) / CLOCKS_PER_NANOSECOND);
    delete _solveRecursive_bestKnapsack;
    delete _solveRecursive_knapsack;
    return solution;
}

void KnapsackSolver::_solveDynamic_grain(int n, int m) {
    if (_solveDynamic_matrix[n][m] == 0) {
        return;
    }
    if (n > 0 && _solveDynamic_matrix[n - 1][m] == _solveDynamic_matrix[n][m]) {
        _solveDynamic_grain(n - 1, m);
    }
    else {
        if (n > 0) {
            _solveDynamic_grain(n - 1, m - (*_solveDynamic_items)[n].weight);
        }
        _solveDynamic_knapsack->push_back((*_solveDynamic_items)[n]);
    }
}

KnapsackSolver::Solution KnapsackSolver::solveDynamic() {
    if (_currentProblem >= _problems.size()) {
        throw length_error("No problem to solve.\n");
    }
    // Setting time
    uint64_t t = __rdtsc();

    Problem problem = _problems[_currentProblem];
    int n = problem.itemsNumber;
    int m = problem.maxWeight;
    _solveDynamic_matrix = new int *[n];
    for (int i = 0; i < n; i++) {
        _solveDynamic_matrix[i] = new int[m];
        _solveDynamic_matrix[i][0] = (*problem.items)[i].weight > 1 ? 0 : (*problem.items)[i].cost;
    }
    for (int i = 0; i < m; i++) {
        _solveDynamic_matrix[0][i] = (*problem.items)[i].weight > i + 1 ? 0 : (*problem.items)[i].cost;
    }
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            _solveDynamic_matrix[i][j] = (*problem.items)[i].weight > j + 1 ?
                                         max(_solveDynamic_matrix[i - 1][j], (*problem.items)[i].cost) :
                                         _solveDynamic_matrix[i - 1][j];
            int a;
        }
    }

    /*
     * debuf
     */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            cout << _solveDynamic_matrix[i][j] << " ";
        cout << endl;
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

    Solution solution = Solution(bestWeight, bestCost, bestSize, _solveDynamic_knapsack, DYNAMIC,
                                 ((__rdtsc() - t) / CLOCKS_PER_NANOSECOND) / CLOCKS_PER_NANOSECOND);
    delete[] _solveDynamic_matrix;
    return solution;
}

KnapsackSolver::Solution KnapsackSolver::solveGreedy() {
    return Solution();
}


#include<algorithm> // for one-line lambda-based std::max

KnapsackSolver::KnapsackSolver(vector<Problem> problems) {
    if (problems.empty()) {
        throw length_error("Passed empty problems set.");
    }
    _problems = problems;
    _numberOfTests = problems.size();
    _currentProblem = 0;
}

vector<KnapsackSolver::Problem> *KnapsackSolver::problemsFromFile(string inputPath, string outputPath) {
    ifstream inputStream;
    inputStream.open(inputPath);
    int numberOfTests;
    inputStream >> numberOfTests;
    if (numberOfTests < 1) {
        inputStream.close();
        throw length_error("Passed empty problems set.");
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

KnapsackSolver::Solution KnapsackSolver::solve(int problemNumber, Method method) {
    _currentProblem = problemNumber;
    switch (method) {
        case ITERATIVE:
            return solveIterative();
        case RECURSIVE:
            return solveRecursive();
        case DYNAMIC:
            return solveDynamic();
        case GREEDY:
            return solveGreedy();
        case ALL:
        default:
            return std::max(
                    {solveIterative(), solveRecursive(), solveDynamic(), solveGreedy()},
                    [](Solution ks1, Solution ks2) {
                        return ks1.cost == ks2.cost ? (ks1.time > ks2.time) : (ks1.cost < ks2.cost);
                    });
    }

}

void KnapsackSolver::solve(Method method) {
    _solutions.clear();
    for (int testNumber = 0; testNumber < _numberOfTests; testNumber++) {
        for (int currentMethod = 0; currentMethod < ALL; currentMethod++) {
            _solutions.push_back(solve(testNumber, Method(currentMethod)));
        }
    }
}

KnapsackSolver::~KnapsackSolver() {
}

KnapsackSolver::Item::Item(int number, int weight, int cost) : number(number), weight(weight), cost(cost) { }

KnapsackSolver::Problem::Problem(int maxWeight, int itemsNumber, vector<Item> *items)
        : maxWeight(maxWeight), itemsNumber(itemsNumber),
          items(items) { }

KnapsackSolver::Solution::Solution(int weight, int cost, int itemsNumber, vector<Item> *items, Method method,
                                   int64_t time)
        : weight(weight), cost(cost), itemsNumber(itemsNumber), items(items), method(method), time(time) { }