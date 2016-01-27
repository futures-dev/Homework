//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 27.01.2016
//

#include "StackMachine.h"

#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <stdexcept>

using namespace std;
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
// class MultiplyOp
//==============================================================================

int MultiplyOp::operation(int a, int b, int c) {
    return a * b;
}

IOperation::Arity MultiplyOp::getArity() const {
    return arDue;
}

/*


//==============================================================================
// class DivideOp
//==============================================================================

int DivideOp::operation(int a, int b, int c) {
    if (b == 0) {
        return a >= 0 ? SIZE_MAX : -SIZE_MAX;
    }
    else {
        return a / b;
    }
}

IOperation::Arity DivideOp::getArity() const {
    return arDue;
}
 */

//==============================================================================
// class StackMachine
//==============================================================================


void StackMachine::registerOperation(char symb, IOperation *oper) {
    // prevent multiple registration
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end())
        throw std::logic_error("Operation " + string(&symb, 1) + " is already registered");

    _opers[symb] = oper;
}

IOperation *StackMachine::getOperation(char symb) {
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it == _opers.end())
        return nullptr;

    return it->second;
}

int StackMachine::calculate(const std::string &expr, bool clearStack) {

    if (clearStack) {
        _s.clear();
    }
    vector<string> tokens;

    /*
     stringstream stream(expr);
    std::string item;
    while (getline(stream, item, ' ')) {
        if (!item.empty()) {
            tokens.push_back(item);
        }
    }
     */

    splitStr(expr, ' ', tokens);

    // for each token in tokens
    for (std::vector<std::string>::const_iterator it = tokens.begin(); it != tokens.end(); ++it) {
        const string token = *it;
        int val; // token as int
        if (intToStr(token, val)) {
            _s.push(val);
        }
        else {
            if (token.length() != 1) {
                // operations limited to char
                throw logic_error("Promoted token " + token + " is neither a number, nor an operation");
            }
            IOperation *operation = getOperation(token[0]);
            if (!operation) {
                throw logic_error("Invalid operation: " + token);
            }
            switch (operation->getArity()) {
                case IOperation::arUno:
                    _s.push(operation->operation(_s.pop()));
                    break;
                case IOperation::arDue:
                    _s.push(operation->operation(_s.pop(), _s.pop()));
                    break;
                case IOperation::arTre:
                    _s.push(operation->operation(_s.pop(), _s.pop(), _s.pop()));
                    break;
                default:
                    throw logic_error("Unsupported arity");
            }
        }
    }

    return _s.top();
}

