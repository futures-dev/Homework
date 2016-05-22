//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016 
//

#ifndef HOMEWORK_DICTIONARY_H
#define HOMEWORK_DICTIONARY_H

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
class Dictionary {
    Container words;
    const char *wordRegex = "([a-zA-Z][a-zA-Z'\\-]*)";

    struct dictTuple {
        std::string val;
        mutable bool notFound;

        dictTuple(const std::string &val, bool notFound) : val(val), notFound(notFound) { }

        bool operator==(const dictTuple &other) {
            return val == other.val;
        }

        bool operator<(const dictTuple &other) {
            return val < other.val;
        }
    };

public:
    Dictionary(const std::string &input) {
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

    Dictionary() { }

    uint64_t compareText(const std::string &input, const std::string &output) {
        {
            using namespace std;
            ifstream fin(input);
            if (!fin.is_open()) {
                throw invalid_argument("File" + input + " Not Found");
            }
            cout << "Loading file: " + input << endl;
            set<dictTuple> textWords;
            string buf;
            regex e(wordRegex, regex_constants::basic);
            while (getline(fin, buf)) {
                smatch match;
                regex_search(buf, match, e);
                for (auto word:match) {
                    //transform(word.str().begin(),word.str().end(),word.str().begin(),::tolower);
                    textWords.emplace(word.str(), false);
                }
            }
            cout << "Process words..." << endl;
            uint64_t time = __rdtsc();
            int len = textWords.size();
            for (auto it = textWords.begin(); it != textWords.end(); it++) {
                if (!words.search(it->val)) {
                    it->notFound = true;
                }
            }
            time = __rdtsc() - time;

            ofstream fout(output);
            cout << "List of words not found in dictionary:" << endl;
            for (auto word:textWords) {
                if (word.notFound) {
                    fout << word.val << endl;
                    cout << word.val << endl;
                }
            }
            return time;
        }
    }
};

#endif //HOMEWORK_DICTIONARY_H
