// parts.h

//
// Andrei Kolomiets 143-1
// CLion 2016.1.1 MinGW 3.2.1
// 26.04.2016
//

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

//**************** Part ****************
class Part {
private:
    friend map<Part *, int> subpartsNumbers;

public:
    string name;

    Part(string const &n) : name(n) { };

    // Prints Part description
    void describe(void) const;

    // Returns quantity of specified parts in caller
    int countHowMany(Part const *p) const;

    // For Part to be used as a map key
    bool operator<(const Part &other) const;
};

//**************** NameContainer ****************
class NameContainer {

private:
    map<string, Part *> nameMap;

public:

    NameContainer(void) { };

    // Destroy created in @lookup Parts
    ~NameContainer();

    // Includes n=quantity subparts into part
    void addPart(string const &part, int quantity, string const &subpart);

    // Returns a pointer to a Part with specified name
    Part *lookup(string const &name);
};

#endif
