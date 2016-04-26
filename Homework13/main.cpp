// main.cpp -- driver program for "Sum of Its Parts"

#pragma warning(disable:4786)

#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

#include "parts.h"

NameContainer partContainer;


void loadDefinitions(const char *filename) {
    ifstream inf(filename);
    string part, subpart;
    int quantity;

    while (inf.good()) {
        inf >> part >> quantity >> subpart;
        if (!inf.good()) return;
        partContainer.addPart(part, quantity, subpart);
    }
}

void whatisQuery(string const &x) {

    Part *xp = partContainer.lookup(x);
    cout << endl;
    xp->describe();
}

void howmanyQuery(string const &x, string const &y) {

    Part *xp = partContainer.lookup(x);
    Part *yp = partContainer.lookup(y);
    cout << endl << y << " has " << yp->countHowMany(xp) << " " << x << endl;
}

void processQueries(const char *filename) {

    ifstream inf(filename);
    string query, x, y;

    while (inf.good()) {
        inf >> query >> x;

        if (query == "howmany")
            inf >> y;

        if (!inf.good()) return;

        if (query == "howmany")
            howmanyQuery(x, y);
        else if (query == "whatis")
            whatisQuery(x);
        else {
            cerr << "*** Illegal query: " << query << endl;
            return;
        }
    }
}

int main(void) {
    loadDefinitions("definitions.txt");
    processQueries("queries.txt");
    return EXIT_SUCCESS;
}
