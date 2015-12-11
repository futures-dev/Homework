//
// Created by Computer on 06.12.2015.
//

#include <iostream>
#include "KnapsackSolver.h"
#include <chrono>

using namespace chrono;

KnapsackSolver::Solution KnapsackSolver::solveIterative(Problem problem) {

    // Setting time
    auto start = high_resolution_clock::now();

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
        currentItem = knapsack->back().number;
        knapsack->pop_back();
        currentItem++;
    }

    // Preparing the answer
    int bestWeight = 0;
    knapsack->resize(bestSize);
    for (int i = 0; i < bestSize; i++) {
        (*knapsack)[i] = (*problem.items)[bestKnapsack[i]];
        bestWeight += (*knapsack)[i].weight;
    }
    Solution solution = Solution(bestWeight, bestCost, bestSize, knapsack, ITERATIVE,
                                 duration_cast<nanoseconds>(high_resolution_clock::now() - start).count());

    return solution;
}


KnapsackSolver::Solution KnapsackSolver::solveRecursive(Problem problem) {
    return Solution();
}

KnapsackSolver::Solution KnapsackSolver::solveDynamic(Problem problem) {
    return Solution();
}

KnapsackSolver::Solution KnapsackSolver::solveGreedy(Problem problem) {
    return Solution();
}


#include<algorithm> // for one-line lambda-based std::max

KnapsackSolver::KnapsackSolver(string inputPath, string outputPath) {
    if (inputPath == "test") {
        int n = 22;
        vector<Item> *items = new vector<Item>();
        items->reserve(n);

        items->push_back(Item(0, 9, 150));
        items->push_back(Item(1, 13, 35));
        items->push_back(Item(2, 153, 200));
        items->push_back(Item(3, 50, 160));
        items->push_back(Item(4, 15, 60));
        items->push_back(Item(5, 68, 45));
        items->push_back(Item(6, 27, 60));
        items->push_back(Item(7, 39, 40));
        items->push_back(Item(8, 23, 30));
        items->push_back(Item(9, 52, 10));
        items->push_back(Item(10, 11, 70));
        items->push_back(Item(11, 32, 30));
        items->push_back(Item(12, 24, 15));
        items->push_back(Item(13, 48, 10));
        items->push_back(Item(14, 73, 40));
        items->push_back(Item(15, 42, 70));
        items->push_back(Item(16, 43, 75));
        items->push_back(Item(17, 22, 80));
        items->push_back(Item(18, 7, 20));
        items->push_back(Item(19, 18, 12));
        items->push_back(Item(20, 4, 50));
        items->push_back(Item(21, 30, 10));
        /*
       items->push_back(Item(0, 12, 4));
       items->push_back(Item(1, 2, 2));
       items->push_back(Item(2, 1, 2));
       items->push_back(Item(3, 1, 1));
       items->push_back(Item(4, 4, 10));*/
        Problem problem(400, n, items);
        Solution solution = solveIterative(problem);
        cout << solution.time << endl;
        for (int i = 0; i < solution.itemsNumber; i++)
            cout << (*solution.items)[i].number << " ";
    }
    else {
        _inputPath = inputPath;
        _outputPath = outputPath;
        ifstream inputStream;
        inputStream.open(_inputPath);
        inputStream >> _numberOfTests;
        _problems = new vector<Problem>();
        _problems->reserve(_numberOfTests);
        for (int testNumber = 0; testNumber < _numberOfTests; testNumber++) {
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
            _problems->push_back(Problem(maxWeight, itemsNumber, items));
        }
        _solutions = new vector<Solution>();
    }

}

KnapsackSolver::Solution KnapsackSolver::solve(Problem problem, Method method) {
    switch (method) {
        case ITERATIVE:
            return solveIterative(problem);
        case RECURSIVE:
            return solveRecursive(problem);
        case DYNAMIC:
            return solveDynamic(problem);
        case GREEDY:
            return solveGreedy(problem);
        case ALL:
        default:
            return std::max(
                    {solveIterative(problem), solveRecursive(problem), solveDynamic(problem), solveGreedy(problem)},
                    [](Solution ks1, Solution ks2) {
                        return ks1.cost == ks2.cost ? (ks1.time > ks2.time) : (ks1.cost < ks2.cost);
                    });
    }

}

void KnapsackSolver::solve(Method method) {
    _solutions->clear();
    for (int testNumber = 0; testNumber < _numberOfTests; testNumber++) {
        for (int currentMethod = 0; currentMethod < ALL; currentMethod++) {
            _solutions->push_back(solve((*_problems)[testNumber], Method(currentMethod)));
        }
    }
}

KnapsackSolver::~KnapsackSolver() {
    delete[] _problems;
    delete[] _solutions;
}

KnapsackSolver::Item::Item(int number, int weight, int cost) : number(number), weight(weight), cost(cost) { }

KnapsackSolver::Problem::Problem(int maxWeight, int itemsNumber, vector<Item> *items)
        : maxWeight(maxWeight), itemsNumber(itemsNumber),
          items(items) { }

KnapsackSolver::Solution::Solution(int weight, int cost, int itemsNumber, vector<Item> *items, Method method,
                                   int64_t time)
        : weight(weight), cost(cost), itemsNumber(itemsNumber), items(items), method(method), time(time) { }

KnapsackSolver::Solution::~Solution() {
    delete[] items;
}

KnapsackSolver::Problem::~Problem() {
    delete[] items;
}