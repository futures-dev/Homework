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

	KnapsackTester();
	virtual ~KnapsackTester();

private:

	vector<Problem> _check_problems;
	vector<int> _check_costs;
public:
    void problemsFromFile();
	void solve();
	void resolveAll();
};


#endif //KDZ_KNAPSACKTESTER_H
