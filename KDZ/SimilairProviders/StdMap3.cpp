//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 25.05.2016
//

#include "StdMap3.h"
#include <iostream>
#include <fstream>

using namespace std;

void StdMap3::insert(const string &word, const StringContainer &dict) {
    set<string> suggestions;
    this->suggest_replacement(word, dict, suggestions);
    int len = word.length();
    auto map = words[word[0]][len];
    auto it2 = map.find(word);
    if (it2 == map.end()) {
        map[word] = suggestions;
    }
    else {
        it2->second.insert(suggestions.begin(), suggestions.end());
    }
}

set<string> StdMap3::operator[](const string &word) const {
    // find because operator[] is not const
    auto bin = words.find(word[0])->second;
    auto it = bin.find(word.length());
    if (it != bin.end()) {
        auto it2 = it->second.find(word);
        if (it2 != it->second.end()) {
            return it2->second;
        }
    }
    return set<string>();
}

void StdMap3::output(const string &output) const {
    ofstream fout(output);
    for (auto it = words.begin(); it != words.end(); it++) {
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            for (auto it3 = it2->second.begin(); it3 != it2->second.end(); it3++) {
                auto it4 = it3->second.begin();
                if (it4 != it3->second.end()) {
                    fout << "Word: " << it3->first << endl;
                    fout << "Suggestions: " << endl;
                    for (; it4 != it3->second.end(); it4++) {
                        fout << "\t" << *it4 << endl;
                    }
                }
            }
        }
    }
    cout << "StdMap output done." << endl;
}