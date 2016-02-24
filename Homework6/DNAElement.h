#ifndef DNAELEMENT_H
#define DNAELEMENT_H

#include <iostream>
#include <string>

using namespace std;

class DNAElement {
public:
    void readString(string description);
    /**
     * Constructor
     * Fill the fields id, number, base from a description in the format [name][number]:[type] where
     * [id] - a..z
     * [number] - the number of this element in the DNA sequence a1 a2 a3 a4 a5...
     * [base] - biological component of the element (A, C, T or G)
     *
     * So for description "a1:G"
     * name = "a";
     * number = 1;
     * type = "G";
     *
     * Throws invalid_argument if the format is wrong
     *                      or if the type of element is not in [A, C, T, G]
     */

public:
    // Public members (WARNING: it is very bad in industry to have public members)

    string id;
    // The id of the DNA element

    int number;
    // The number of the DNA element

    string base;
    // Base of the DNA element

};

#endif
