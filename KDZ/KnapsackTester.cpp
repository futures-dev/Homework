//
// Created by Computer on 11.12.2015.
//

#include "KnapsackTester.h"

void KnapsackTester::testSolveStatic() {
    // Test #1
    // Simple array
    cout << "Test #1" << endl;
    vector<Item> *items1 = new vector<Item>();
    items1->push_back(Item(0, 12, 4));
    items1->push_back(Item(1, 2, 2));
    items1->push_back(Item(2, 1, 2));
    items1->push_back(Item(3, 1, 1));
    items1->push_back(Item(4, 4, 10));
    Problem problem1(5, 5, items1);
    vector<Item> *answer1 = new vector<Item>();
    answer1->push_back(Item(2, 1, 2));
    answer1->push_back(Item(4, 4, 10));
    Solution solution1 = Solution(5, 12, 2, answer1, Method::ITERATIVE, 1);
    Solution check1 = KnapsackSolver::solve(problem1, Method::ITERATIVE);
    if (check1.weight != solution1.weight)
        cout << "weight: " << check1.weight << " .Instead of: " << solution1.weight << endl;
    if (check1.cost != solution1.cost)
        cout << "cost: " << check1.cost << " .Instead of: " << solution1.cost << endl;
    cout << "Time: " << check1.time << "ns." << endl;
    delete items1;
    delete answer1;

    // Test #2
    // Complicated array
    cout << "Test #2" << endl;
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
    Problem problem2(400, 22, items2);
    vector<Item> *answer2 = new vector<Item>();
    answer2->push_back(Item(0, 9, 150));
    answer2->push_back(Item(1, 13, 35));
    answer2->push_back(Item(2, 153, 200));
    answer2->push_back(Item(3, 50, 160));
    answer2->push_back(Item(4, 15, 60));
    answer2->push_back(Item(6, 27, 60));
    answer2->push_back(Item(10, 11, 70));
    answer2->push_back(Item(15, 42, 70));
    answer2->push_back(Item(16, 43, 75));
    answer2->push_back(Item(17, 22, 80));
    answer2->push_back(Item(18, 7, 20));
    answer2->push_back(Item(20, 4, 50));
    Solution solution2 = Solution(396, 1030, 12, answer2, Method::ITERATIVE, 1);
    Solution check2 = KnapsackSolver::solve(problem2, Method::ITERATIVE);
    if (check2.weight != solution2.weight)
        cout << "weight: " << check2.weight << " .Instead of: " << solution2.weight << endl;
    if (check2.cost != solution2.cost)
        cout << "cost: " << check2.cost << " .Instead of: " << solution2.cost << endl;
    cout << "Time: " << check2.time << "ns." << endl;
    delete items2;
    delete answer2;
}