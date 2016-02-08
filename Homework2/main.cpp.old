//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 27.01.2016
//

#include <iostream>
#include <assert.h>
#include <stdexcept>
#include <stdio.h>
//#include <conio.h>


#include "IntStack.h"
#include "StackMachine.h"


using namespace std;

void testStack() {
    IntStack s;

    s.push(42);
    //int a = s.pop();
    assert(s.top() == 42);            // EXPECT_EQ()
    assert(s.pop() == 42);            // EXPECT_EQ()

    // an exception should be thrown
    bool exc = false;
    try {
        s.pop();
    }
    catch (std::logic_error &e) {
        std::cout << "An expected exception on pop() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    // test for overflow
    for (int i = 0; i < IntStack::STACK_SIZE; ++i)
        s.push(i);

    // next element cannot be added and, thus, en exception should be thrown
    exc = false;
    try {
        s.push(43);
    }
    catch (std::logic_error &e) {
        std::cout << "An expected exception on push() operation is succesfully catched\n";
        exc = true;
    }
    assert(exc);

    //int b = 0;
}

void testStackMachine() {
    StackMachine sm;
    PlusOp plusop;
    sm.registerOperation('+', &plusop);

    int res = sm.calculate("15 10 +");
    int r1 = sm.getStack().top();
    assert(res == 25);
    assert(r1 == 25);

}

void testStackMachine2() {

    StackMachine sm;
    PlusOp plusop;
    sm.registerOperation('+', &plusop);

    MultiplyOp multiplyOp;
    sm.registerOperation('*', &multiplyOp);

    int res = sm.calculate("15 10 +");
    int r1 = sm.getStack().top();
    assert(res == 25);
    assert(r1 == 25);
    // 25 still on stack
    res = sm.calculate("5 * 3 4 + *", false);
    assert(res == 875);
}

int main() {
    cout << "Hello, World!" << endl;

    testStack();
    testStackMachine();
    testStackMachine2();
    getchar();
    return 0;
}