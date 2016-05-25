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

using namespace std;

template<class Container>
class Dictionary {
    Container words;
    const char *wordRegex = "([a-zA-Z][a-zA-Z'\\-]*)";

    struct dictTuple {
        string val;
        mutable int index;

        dictTuple(const string &val, int index) : val(val), index(index) { }

        bool operator==(const dictTuple &other) {
            return val == other.val;
        }

        bool operator<(const dictTuple &other) {
            return val < other.val;
        }
    };

    void loadWords(const string &input, const set<dictTuple> &textWords) {

        ifstream fin(input);
        if (!fin.is_open()) {
            throw invalid_argument("File" + input + " Not Found");
        }
        cout << "Loading file: " + input << endl;
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
    }


    void suggest_insertion(const string &a_word, set<string> &suggestions) {
        string word(a_word);
        int len = word.length();
        for (int i = 0; i <= len; i++) {
            // insert before i-th letter
            word.insert(i, 1, 'a');
            while (word[i] <= 'z') {
                if (words.search(word)) {
                    suggestions.insert(word);
                }
                word[i]++;
            }
            word.erase(i, 1);
        }
    }

    void suggest_replacement(const string &a_word, set<string> &suggestions) {
        string word(a_word);
        int len = word.length();
        char temp;
        for (int i = 0; i < len; i++) {
            // replace i-th letter
            temp = word[i];
            for (char c = 'a'; c <= 'z'; c++) {
                // replace by c char
                if (c == temp) {
                    // same word
                    continue;
                }
                word[i] = c;
                if (words.search(word)) {
                    suggestions.insert(word);
                }
            }
            word[i] = temp;
        }
    }

    void suggest_odd(const string &a_word, set<string> &suggestions) {
        string word(a_word);
        int len = word.length();
        char temp;
        for (int i = 0; i < len; i++) {
            // erase i-th letter
            temp = word[i];
            word.erase(i, 1);
            if (words.search(word)) {
                suggestions.insert(word);
            }
            // insert back
            word.insert(i, 1, temp);
        }
    }

    void suggest_adjacent(const string &a_word, set<string> &suggestions) {
        string word(a_word);
        int len = word.length();
        char temp;
        for (int i = 1; i < len; i++) {
            // swap i-1 -th and i-th letters
            temp = word[i - 1];
            word[i - 1] = word[i];
            word[i] = temp;
            if (words.search(word)) {
                suggestions.insert(word);
            }
            word[i] = word[i - 1];
            word[i - 1] = temp;
        }
    }

public:
    Dictionary(const string &input) {

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

    uint64_t compareText(const string &input, const string &output) {

        set<dictTuple> textWords;
        loadWords(input, textWords);
        cout << "Process words..." << endl;
        uint64_t time = __rdtsc();
        int len = textWords.size();
        for (auto it = textWords.begin(); it != textWords.end(); it++) {
            if (!words.search(it->val)) {
                it->index = 1;
            }
        }
        time = __rdtsc() - time;

        ofstream fout(output);
        cout << "List of words not found in dictionary:" << endl;
        for (auto word:textWords) {
            if (word.index > 0) {
                fout << word.val << endl;
                cout << word.val << endl;
            }
        }
        return time;
    }

    uint64_t compareDict(const string &input, const string &output) {

        set<dictTuple> textWords;
        loadWords(input, textWords);
        cout << "Process words..." << endl;
        uint64_t time = __rdtsc();
        int len = textWords.size();
        vector<set<string>> newWords;
        int lineN = 0;
        for (auto it = textWords.begin(); it != textWords.end(); it++, lineN++) {
            if (!words.search(it->val)) {
                it->index = lineN;
                newWords.push_back(set<string>());
                suggest_adjacent(it->val, newWords.back());
                suggest_insertion(it->val, newWords.back());
                suggest_odd(it->val, newWords.back());
            }
        }
        time = __rdtsc() - time;

        ofstream fout(output);
        cout << "List of words not found in dictionary:" << endl;
        auto it = newWords.begin();
        for (auto word:textWords) {
            if (word.index > 0) {
                cout << "\tLine " << word.index << ": " << word.val << endl;
                if (!it->empty()) {
                    cout << "\tSuggestions:" << endl;
                }
                fout << word.index << " " << word.val << endl;
                for (auto suggestion : *it) {
                    fout << suggestion << endl;
                    cout << "\t\t" << suggestion << endl;
                }
                it++;
            }
        }
        return time;
    }

    template<class SimilairProvider>
    uint64_t findSimilair(const std::string &input, const std::string &output) {
        using namespace std;

        SimilairProvider provider;
        set<dictTuple> textWords;
        loadWords(input, textWords);

        cout << "Searching similair words..." << endl;
        uint64_t time = __rdtsc();
        for (auto it = textWords.begin(); it != textWords.end(); it++) {
            provider.insert(it->val, words);
        }
        for (auto it = textWords.begin(); it != textWords.end(); it++) {
            provider[it->val];
        }
        time = __rdtsc() - time;
        provider.output(output);
        return time;
    }


};

#endif //HOMEWORK_DICTIONARY_H
