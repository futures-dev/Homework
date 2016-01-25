//
// Created by sergey on 24.01.2016.
//

#include "StackMachine.h"
#include <vector>
#include <sstream>

using namespace std;

//==============================================================================
// Free functions -- helpers
//==============================================================================

// TBD:

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


// TBD
void StackMachine::registerOperation(char symb, IOperation *oper) {
    SymbolToOperMapConstIter it = _opers.find(symb);
    if (it != _opers.end()) {
        throw std::logic_error("An operation is already registered...");
    }
    _opers[symb] = oper;
}

IOperation *StackMachine::getOperation(char symb) {
    return _opers[symb];
}

bool parseInt(string s, int *out) {
    int temp = 0;
    int dec = 1;
    for (int i = s.length() - 1; i >= 0; i++) {
        int outnew = temp + dec * (s.at(i) - '0');
        if (outnew % dec != temp) {
            return false;
        }
        dec *= 10;
    }
    *out = temp;
    return true;
}

int StackMachine::calculate(const std::string &expr, bool clearStack) {
    if (clearStack) {
        _s.clear();
    }
    vector<string> tokens;
    stringstream stream(expr);
    std::string item;
    while (getline(stream, item, ' ')) {
        if (!item.empty()) {
            tokens.push_back(item);
        }
    }

    while (!tokens.empty()) {
        int val;
        if (parseInt(tokens.back(), &val)) {
            _s.push(val);
        }
        else {
            if (tokens.back().length() != 1) {
                throw logic_error("Promoted token is neither a number, nor an operation");
            }
            IOperation *operation = _opers[tokens.back().at(0)];
            switch (operation->getArity()) {
                case IOperation::arUno:
                    _s.push(operation->operation(_s.pop()));
                    break;
                case IOperation::arDue:
                    _s.push(operation->operation(_s.pop(), operation->operation(_s.pop(), _s.pop())));
                    break;
                case IOperation::arTre:
                    _s.push(operation->operation(_s.pop(), operation->operation(_s.pop(), _s.pop()),
                                                 operation->operation(_s.pop(), _s.pop(), _s.pop())));
                    break;
                default:
                    throw logic_error("Unsupported arity");
            }
        }
    }

    return _s.pop();
}

int DivOp::operation(int a, int b, int c) {
    if (b == 0) {
        return a >= 0 ? SIZE_MAX : -SIZE_MAX;
    }
    else {
        return a / b;
    }
}

IOperation::Arity DivOp::getArity() const {
    return arDue;
}
