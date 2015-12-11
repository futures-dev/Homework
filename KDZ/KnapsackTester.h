//
// Created by Computer on 11.12.2015.
//

#ifndef KDZ_KNAPSACKTESTER_H
#define KDZ_KNAPSACKTESTER_H

#include <iostream>
#include "KnapsackSolver.h"

using Item=KnapsackSolver::Item;
using Problem=KnapsackSolver::Problem;
using Method=KnapsackSolver::Method;
using Solution=KnapsackSolver::Solution;
using namespace std;

class KnapsackTester {
public:
    void testSolveStatic();
};


#endif //KDZ_KNAPSACKTESTER_H
