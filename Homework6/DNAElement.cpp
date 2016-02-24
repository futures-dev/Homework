//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 24.02.2016
//

#include <stdexcept>
#include "DNAElement.h"

void DNAElement::readString(string description) {

    // check length
    if (description.length() != 4) {
        throw std::invalid_argument("Invalid DNA token length");
    }
    char temp; // store symbols in process

    // check id
    temp = description[0];
    if (temp > 'z' || temp < 'a') {
        throw std::invalid_argument("Invalid DNA id");
    }
    id = temp;

    // check number
    temp = description[1];
    if (temp > '9' || temp < '0') {
        throw std::invalid_argument("Invalid DNA number");
    }
    number = temp - '0';
    if (description[2] != ':') {
        throw std::invalid_argument("Unexpected DNA token symbol");
    }

    // check base
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