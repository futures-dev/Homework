//
// Created by Computer on 24.02.2016.
//

#include <stdexcept>
#include "DNAElement.h"

void DNAElement::readString(string description) {
    if (description.length() != 4) {
        throw std::invalid_argument("Invalid DNA token length");
    }
    char temp;
    temp = description[0];
    if (temp > 'z' || temp < 'a') {
        throw std::invalid_argument("Invalid DNA id");
    }
    id = temp;
    temp = description[1];
    if (temp > '9' || temp < '0') {
        throw std::invalid_argument("Invalid DNA number");
    }
    number = temp - '0';
    if (description[2] != ':') {
        throw std::invalid_argument("Unexpected DNA token symbol");
    }
    temp = description[3];
    switch (temp) {
        case 'A':
        case 'C':
        case 'G':
        case 'T':
            base = temp;
            break;
        default:
            throw std::invalid_argument("Invalid DNA base");
    }
}