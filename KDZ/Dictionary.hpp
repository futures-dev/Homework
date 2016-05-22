//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#ifndef HOMEWORK_DICTIONARY_H
#define HOMEWORK_DICTIONARY_H

#include "Dictionary.h"
#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>
#include <set>
#include <regex>

#ifdef _MSC_VER
#include <intrin.h>
#else

#include <x86intrin.h>

#endif

template<class Container>
Dictionary<Container>::Dictionary(const std::string &input) {
    using namespace std;
    ifstream fin(input);
    string buf;
    if (!fin.is_open()) {
        throw invalid_argument("File" + input + " Not Found");
    }
    while (getline(fin, buf)) {
        words.insert(buf);
    }
}

template<class Container>
uint64_t Dictionary<Container>::compareText(const std::string &input, const std::string &output) {
    {
        using namespace std;
        ifstream fin(input);
        if (!fin.is_open()) {
            throw invalid_argument("File" + input + " Not Found");
        }
        cout << "Loading file: " + input << endl;
        set<pair<string, bool>> textWords;
        string buf;
        regex e(wordRegex, regex_constants::basic);
        while (getline(fin, buf)) {
            smatch match;
            regex_search(buf, match, e);
            for (auto word:match) {
                textWords.emplace(buf, false);
            }
        }
        cout << "Process words..." << endl;
        uint64_t time = __rdtsc();
        int len = textWords.size();
        for (auto word:textWords) {
            if (!words.search(word.first)) {
                word.second = true;
            }
        }
        time = __rdtsc() - time;

        ofstream fout(output);
        cout << "List of words not found in dictionary:" << endl;
        for (auto word:textWords) {
            if (word.second) {
                fout << word.first << endl;
                cout << word.first << endl;
            }
        }
        return time;
    }
}

#endif //HOMEWORK_DICTIONARY_H
