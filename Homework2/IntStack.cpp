//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 27.01.2016
//

#include <stdexcept>
#include "IntStack.h"

IntStack::IntStack(size_t sz) {
    _stack = new int[_ssize = sz]; // Allocate stack
    _head = -1; // Set current head
}

IntStack::~IntStack() {
    delete _stack; // Free memory
}

void IntStack::push(int el) {
    // size_t is unsigned
    if (++_head >= _ssize) {
        throw std::logic_error("Stack overflow");
    }
    _stack[_head] = el;
}

int IntStack::pop() {
    if (_head >= _ssize) {
        throw std::logic_error("Stack is empty");
    }
    return _stack[_head--];
}

int IntStack::top() {
    if (_head >= _ssize) {
        throw std::logic_error("Stack is empty");
    }
    return _stack[_head];
}

void IntStack::clear() {
    // init not needed
    _head = -1;
}
