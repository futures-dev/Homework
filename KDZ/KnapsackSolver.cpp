//
// Created by Computer on 06.12.2015.
//

#include "KnapsackSolver.h"

KnapsackSolver::Solution KnapsackSolver::solveIterative(KnapsackSolver::Problem problem) {
    return KnapsackSolver::Solution();
}

KnapsackSolver::Solution KnapsackSolver::solveRecursive(KnapsackSolver::Problem problem) {
    return KnapsackSolver::Solution();
}

KnapsackSolver::Solution KnapsackSolver::solveDynamic(KnapsackSolver::Problem problem) {
    return KnapsackSolver::Solution();
}

KnapsackSolver::Solution KnapsackSolver::solveGreedy(KnapsackSolver::Problem problem) {
    return KnapsackSolver::Solution();
}

#include<algorithm> // for one-line lambda-based std::max

KnapsackSolver::KnapsackSolver(string inputPath = "input_knap.txt", string outputPath = "output_knap.txt") {
    _inputPath = inputPath;
    _outputPath = outputPath;
    ifstream inputStream;
    inputStream.open(_inputPath);
    inputStream >> _numberOfTests;
    _problems = new vector<Problem>();
    for (int testNumber = 0; testNumber < _numberOfTests; testNumber++) {
        int maxWeight;
        inputStream >> maxWeight;
        int itemsNumber;
        inputStream >> itemsNumber;
        int *itemsWeights = new int[itemsNumber];
        for (int i = 0; i < itemsNumber; i++) {
            inputStream >> itemsWeights[i];
        }
        int *itemsCosts = new int[itemsNumber];
        for (int i = 0; i < itemsNumber; i++) {
            inputStream >> itemsCosts[i];
        }
        _problems->push_back({maxWeight, itemsNumber, itemsWeights, itemsCosts});
    }
    _solutions = new vector<Solution>();
}

KnapsackSolver::Solution KnapsackSolver::solve(KnapsackSolver::Problem problem, KnapsackSolver::Method method) {
    switch (method) {
        case Method::ITERATIVE:
            return solveIterative(problem);
        case Method::RECURSIVE:
            return solveRecursive(problem);
        case Method::DYNAMIC:
            return solveDynamic(problem);
        case Method::GREEDY:
            return solveGreedy(problem);
        case Method::ALL:
            return std::max(
                    {solveIterative(problem), solveRecursive(problem), solveDynamic(problem), solveGreedy(problem)},
                    [](KnapsackSolver::Solution ks1, KnapsackSolver::Solution ks2) {
                        return ks1.cost < ks2.cost;
                    });
        default:
            return KnapsackSolver::Solution(); // Not supposed to end up here
    }

}

void KnapsackSolver::solve(KnapsackSolver::Method method) {
    _solutions->clear();
    for (int testNumber = 0; testNumber < _numberOfTests; testNumber++) {
        for (int currentMethod = 0; currentMethod < Method::ALL; currentMethod++) {
            _solutions->push_back(solve((*_problems)[testNumber], (Method) currentMethod));
        }
    }
}

KnapsackSolver::~KnapsackSolver() {
    delete[] _problems;
    delete[] _solutions;
}
