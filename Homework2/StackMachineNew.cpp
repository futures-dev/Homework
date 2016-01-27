//
// Created by sergey on 24.01.2016.
//

#include "StackMachine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

//==============================================================================
// Free functions -- helpers
//==============================================================================

/** Splits given \param s string using given \param delim symbol as delimiter
 *  Puts results tockens into the given \param elems vector
 */
std::vector<std::string> &splitStr(const std::string &s, char delim, std::vector<std::string> &elems) {
    std::stringstream ss(s);
    std::string item;

    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

bool intToStr(const std::string &s, int &i) {
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
        return false;

    char *p = nullptr;
    i = strtol(s.c_str(), &p, 10);

    return (*p == '\0');
}


//==============================================================================
// class PlusOp
//==============================================================================


int PlusOp::operation(int a, int b, int c) {
    // here we just ignore unused operands
    return a + b;
}

IOperation::Arity PlusOp::getArity() const {
    return arDue;
}


//==============================================================================
// class StackMachine
//==============================================================================


void StackMachine::registerOperation(char symb, IOperation *oper) {
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end())
        throw std::logic_error("An operation with the same symbol is already registered");

    _opers[symb] = oper;
}

IOperation *StackMachine::getOperation(char symb) {
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it == _opers.end())
        return nullptr;

    return it->second;
}

int StackMachine::calculate(const std::string &expr, bool clearStack) {
    if (clearStack)
        _s.clear();

    std::vector<std::string> tokens;
    splitStr(expr, ' ', tokens);

    // iterates all tokens
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
        const std::string &curToken = *it;
        int num;
        bool isNum = intToStr(curToken, num);

        // if current token is number, push it onto the stack
        if (isNum) {
            _s.push(num);
            continue;
        }

        // the other possible option is to interpret symbol as operator
        if (curToken.size() != 1)
            throw std::logic_error("Unknown token: " + curToken);

        // well, its size is 1 symbol. try to found an appropriate operation
        IOperation *op = getOperation(curToken[0]);
        if (!op)
            throw std::logic_error("No operation defined: " + curToken);

        // if the operation is defined, the result is determined by its arity
        IOperation::Arity ar = op->getArity();
        int op1 = 0, op2 = 0, op3 = 0;
        if (ar == IOperation::arUno || ar == IOperation::arDue || ar == IOperation::arTre) {
            op1 = _s.pop();
            if (ar == IOperation::arDue || ar == IOperation::arTre) {
                op2 = _s.pop();
                if (ar == IOperation::arTre)
                    op3 = _s.pop();
            }
        }

        int res = op->operation(op1, op2, op3);
        _s.push(res);

        return res;
    }


}
