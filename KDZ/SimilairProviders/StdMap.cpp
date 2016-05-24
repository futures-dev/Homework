//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#include "StdMap.h"
#include <iostream>
#include <fstream>

using namespace std;

void StdMap::insert(const string &word, const StringContainer &dict) {
    set<string> suggestions;
    this->suggest_adjacent(word, dict, suggestions);
    this->suggest_insertion(word, dict, suggestions);
    this->suggest_odd(word, dict, suggestions);
    this->suggest_replacement(word, dict, suggestions);
    auto it = words.find(word);
    if (it == words.end()) {
        words[word] = suggestions;
    }
    else {
        it->second.insert(suggestions.begin(), suggestions.end());
    }
}

set<string> StdMap::operator[](const string &word) const {
    return words.find(word)->second;
}

void StdMap::output(const string &output) const {
    ofstream fout(output);
    for (auto it = words.begin(); it != words.end(); it++) {
        fout << "Word: " << it->first << endl;
        fout << "Suggestions: " << endl;
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            fout << "\t" << *it2 << endl;
        }
    }
    cout << "StdMap output done." << endl;
}