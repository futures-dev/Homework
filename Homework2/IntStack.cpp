//
// Created by Computer on 25.01.2016.
//

#include "IntStack.h"

IntStack::IntStack(size_t sz) {
    _stack = new int[sz];
}

IntStack::~IntStack() {
    delete _stack;
}

void IntStack::push(int el) {
    _stack[_ssize++] = el;
}

int IntStack::pop() {
    return _stack[--_ssize];
}

int IntStack::top() {
    return _stack[_ssize - 1];
}

void IntStack::clear() {
    _ssize = 0;
}
