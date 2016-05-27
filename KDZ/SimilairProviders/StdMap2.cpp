//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 25.05.2016 
//

#include "StdMap2.h"
#include <iostream>
#include <fstream>

using namespace std;

void StdMap2::insert(const string &word, const StringContainer &dict) {
    set<string> suggestions;
    this->suggest_replacement(word, dict, suggestions);
    int len = word.length();
    auto map = words[len];
    auto it2 = map.find(word);
    if (it2 == map.end()) {
        map[word] = suggestions;
    }
    else {
        it2->second.insert(suggestions.begin(), suggestions.end());
    }
}

set<string> StdMap2::operator[](const string &word) const {
    auto it = words.find(word.length());
    if (it != words.end()) {
        auto it2 = it->second.find(word);
        if (it2 != it->second.end()) {
            return it2->second;
        }
    }
    return set<string>();
}

void StdMap2::output(const string &output) const {
    ofstream fout(output);
    for (auto it = words.begin(); it != words.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            auto it3 = it2->second.begin();
            if (it3 != it2->second.end()) {
                fout << "Word: " << it2->first << endl;
                fout << "Suggestions: " << endl;
                for (; it3 != it2->second.end(); it3++) {
                    fout << "\t" << *it3 << endl;
                }
            }
        }
    }
    cout << "StdMap2 output done." << endl;
}