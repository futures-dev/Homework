// parts.h

#ifndef _PARTS_H_
#define _PARTS_H_

#include <vector>
#include <map>
#include <string>

using namespace std;

//**************** Part ****************
class Part {
public:
    string name;

    // TODO: Finish declaration
    map<Part, int> subpartsNumbers;

    Part(string const &n) : name(n) { };

    void describe(void) {
        cout << "Part " << name << " subparts are:" << endl;
        for (auto it = subpartsNumbers.begin(); it != subpartsNumbers.end(); it++) {
            cout << it->->second << " " << it->first << endl;
        }
        cout << endl;
    }

    int countHowMany(Part const *p) {
        int howMany = this == p ? 1 : 0;
        for (auto it = subpartsNumbers.begin(); it != subpartsNumbers.end(); it++) {
            howMany += (it->second) * it->first.countHowMany(p);
        }
        return howMany;
    }
};


//**************** NameContainer ****************
class NameContainer {

private:
    map<string, Part *> nameMap;

public:

    NameContainer(void) { };

    void addPart(string const &part, int quantity, string const &subpart) {
        lookup(part)->subpartsNumbers->insert(Pair(subpart, quantity));
    }

    Part *lookup(string const &name) {
        Part *found = nameMap.find(name);
        if (found == nameMap.end()) {
            found = new Part(name);
            nameMap.insert(found);
        }
        return found;
    }
    // You can add some methods here
};

#endif
