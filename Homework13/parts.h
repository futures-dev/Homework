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
            cout << it->second << " " << it->first.name << endl;
        }
        cout << endl;
    }

    int countHowMany(Part const *p) {
        int howMany = (this == p) ? 1 : 0;
        for (auto it = subpartsNumbers.begin(); it != subpartsNumbers.end(); it++) {
            howMany += (it->second) * it->first.countHowMany(p);
        }
        return howMany;
    }

    bool operator<(const Part &other) const {
        return name < other.name;
    }
};


//**************** NameContainer ****************
class NameContainer {

private:
    map<string, Part *> nameMap;

public:

    NameContainer(void) { };

    void addPart(string const &part, int quantity, string const &subpart) {
        lookup(part)->subpartsNumbers.insert(pair<Part, int>(subpart, quantity));
    }

    Part *lookup(string const &name) {
        auto found = nameMap.find(name);
        if (found == nameMap.end()) {
            Part *part = new Part(name);
            nameMap.insert(pair<string, Part *>(name, part));
            return part;
        }
        return found->second;
    }
    // You can add some methods here
};

#endif
