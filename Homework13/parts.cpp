//
// Andrei Kolomiets 143-1
// CLion 2016.1.1 MinGW 3.2.1
// 26.04.2016
//

#include <iostream>
#include "parts.h"

//**************** Part ****************
int Part::countHowMany(Part const *p) const {
    int howMany = (this == p) ? 1 : 0; // if *this* is being searched, Part contains self
    for (auto it = subpartsNumbers.begin(); it != subpartsNumbers.end(); it++) {
        howMany += (it->second) * it->first->countHowMany(p);
    }
    return howMany;
}

void Part::describe(void) const {
    cout << "Part " << name << " subparts are:" << endl;
    auto it = subpartsNumbers.begin();
    if (it == subpartsNumbers.end()) {
        cout << "It has no subparts." << endl;
    }
    else {
        while (it != subpartsNumbers.end()) {
            cout << it->second << " " << it->first->name << endl;
            it++;
        }
    }
}

//**************** NameContainer ****************
void NameContainer::addPart(string const &part, int quantity, string const &subpart) {
    lookup(part)->subpartsNumbers.insert(pair<Part *, int>(lookup(subpart), quantity));
}

Part *NameContainer::lookup(string const &name) {
    auto found = nameMap.find(name);
    if (found == nameMap.end()) {
        // no part with *name* is stored yet
        // create new one
        Part *part = new Part(name);
        // store it
        nameMap.insert(pair<string, Part *>(name, part));
        // and return it
        return part;
    }
    // part with *name* is already stored, return it
    return found->second;
}

NameContainer::~NameContainer() {
    // delete new parts created in *lookup*
    for (auto it = nameMap.begin(); it != nameMap.end(); it++) {
        if (it->second) {
            delete it->second;
        }
    }
}

bool Part::operator<(const Part &other) const {
    // parts are sorted corresponding to names
    return name < other.name;
}