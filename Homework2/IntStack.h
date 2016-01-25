//
// Created by sergey on 24.01.2016.
// See http://www.stack.nl/~dimitri/doxygen/manual/docblocks.html for Doxygen documenting
//

#ifndef STACKMACHINE_INTSTACK_H
#define STACKMACHINE_INTSTACK_H

#include <stddef.h>     // need fo size_t

/** Declares a stack of integers.
 */
class IntStack {
public:
    // const
    static const int STACK_SIZE = 1024;     ///< Defines a maximum number of stack elements

public:
    // Constructors
    IntStack(size_t sz = STACK_SIZE);           ///< Default constructor
    ~IntStack();

public:
    //----<Main ADT interface>----

    /** Pushes a given element onto the stack.
     *
     *  If no more elements can be placed onto the stack due to its overflow an std::logic_error is thrown.
     */
    void push(int el);

    /** Pops an element from the stack.
     *
     *  If no elements stored in the stack, a std::logic_error is thrown.
     */
    int pop();

    /** Looks up an element from the top of the stack.
     *
     *  If no elements stored in the stack, a std::logic_error is thrown.
     */
    int top();

    /** Clears the stack and makes it empty.
     *
     *  Often named as makeEmpty or similar
     */
    void clear();

protected:
    //int     _stack[STACK_SIZE];             ///< Stack elements as an fixed size array
    int *_stack;                         ///< Stack as a dynamic array
    size_t _ssize;                         ///< Actual stack size
    size_t _head;                          ///< Stack head
}; // class IntStack


#endif //STACKMACHINE_INTSTACK_H
