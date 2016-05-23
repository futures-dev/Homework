//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <regex>
#include <iostream>
#include <set>
#include "SpellChecker.h"

bool SpellChecker::d_search(const string &word) const {
    unsigned char h = hash(word);
    vector<string> &it = hashset[h];
    auto it2 = find(it.begin(), it.end(), word);
    return it2 != it.end();
}

bool SpellChecker::dwd_insert(const string &word) {
    unsigned char h = hash(word);
    vector<string> &it = hashset[h];
    if (find(it.begin(), it.end(), word) == it.end()) {
        it.push_back(word);
        return true;
    }
    else {
        return false;
    }
}

bool SpellChecker::d_delete(const string &word) {
    unsigned char h = hash(word);
    vector<string> &it = hashset[h];
    auto it2 = find(it.begin(), it.end(), word);
    if (it2 != it.end()) {
        it.erase(it2);
        _size--;
        return true;
    }
}

size_t SpellChecker::d_count() const {
    /*
    int c = 0;
    for (auto it = hashset.begin();it!=hashset.end();it++){
        c += it->second.size();
    }
    return c;
     */
    return _size;
}

void SpellChecker::d_print(const string &output, bool sorted) const {
    if (sorted) {
        print_sorted(output);
    }
    else {
        ofstream fout(output);
        for (auto it = 0; it < UINT16_MAX; it++) {
            for (auto it2 = hashset[it].begin(); it2 != hashset[it].end(); it2++) {
                fout << *it2 << endl;
            }
        }
    }
}

void SpellChecker::load_words(const string &input) {
    ifstream fin(input);
    if (!fin.is_open()) {
        throw invalid_argument("File" + input + " Not Found");
    }
    string buf;
    regex e(wordRegex, regex_constants::basic);
    while (getline(fin, buf)) {
        smatch match;
        regex_search(buf, match, e);
        for (auto word:match) {
            //transform(word.str().begin(),word.str().end(),word.str().begin(),::tolower);
            dwd_insert(word.str());
        }
    }
}

void SpellChecker::spell_check(const string &input, const string &output) const {
    ifstream fin(input);
    if (!fin.is_open()) {
        throw invalid_argument("File" + input + " Not Found");
    }
    string buf;
    regex e(wordRegex, regex_constants::basic);
    ofstream fout(output);
    while (getline(fin, buf)) {
        smatch match;
        while (regex_search(buf, match, e)) {
            //transform(word.str().begin(),word.str().end(),word.str().begin(),::tolower);
            fout << match.prefix();
            string word(match.str());
            buf = match.suffix();
            if (!d_search(word)) {
                cout << "Обнаружено слово " << word << " - оно отсутствует в словаре" << endl;
                bool bad_action1 = true;
                while (bad_action1) {
                    cout << POSSIBLE_ACTIONS_STRING << endl;
                    string action_buf;
                    getline(cin, action_buf);
                    switch (action_buf.back()) {
                        case 'R':
                        case 'r': {
                            cout << "Возможно, имелось в виду:" << endl;
                            set<string> suggestions;
                            suggest_adjacent(word, suggestions);
                            suggest_insertion(word, suggestions);
                            suggest_odd(word, suggestions);
                            suggest_replacement(word, suggestions);
                            int i = 0;
                            for (auto it = suggestions.begin(); it != suggestions.end(); it++, i++) {
                                cout << i << ". " << *it << endl;
                            }
                            while (true) {
                                cout << POSSIBLE_REPLACEMENTS_STRING << endl;
                                string action_buf2;
                                getline(cin, action_buf2);
                                if (action_buf2 == "I") {
                                    fout << word;
                                    break;
                                }
                                stringstream myStream(input);
                                int number;
                                if (myStream >> number) {
                                    if (number < i) {
                                        i = 0;
                                        auto it = suggestions.begin();
                                        while (i++ < number) {
                                            it++;
                                        }
                                        fout << *it;
                                        break;
                                    }
                                }
                            }
                            bad_action1 = false;
                            break;
                        }
                        case 'I':
                        case 'i':
                            fout << word;
                            bad_action1 = false;
                            break;
                        case 'X':
                        case 'x':
                            return;
                        default:
                            break;
                    }
                }
            }
        }
        fout << match.suffix();
    }
}

void SpellChecker::print_sorted(const string &output) const {
    vector<string> sorted;
    for (auto it = 0; it != UINT16_MAX; it++) {
        for (auto it2 = hashset[it].begin(); it2 != hashset[it].end(); it2++) {
            sorted.emplace_back(*it2);
        }
    }
    sort(sorted.begin(), sorted.end());
    ofstream fout(output);
    for (auto it = sorted.begin(); it != sorted.end(); it++) {
        fout << *it << endl;
    }
}


void SpellChecker::suggest_insertion(const string &a_word, set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    for (int i = 0; i <= len; i++) {
        // insert before i-th letter
        word.insert(i, 1, 'a');
        while (word[i] <= 'z') {
            if (d_search(word)) {
                suggestions.insert(word);
            }
            word[i]++;
        }
        word.erase(i, 1);
    }
}

void SpellChecker::suggest_replacement(const string &a_word, set<string> &suggestions) const {
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
            if (d_search(word)) {
                suggestions.insert(word);
            }
        }
        word[i] = temp;
    }
}

void SpellChecker::suggest_odd(const string &a_word, set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    char temp;
    for (int i = 0; i < len; i++) {
        // erase i-th letter
        temp = word[i];
        word.erase(i, 1);
        if (d_search(word)) {
            suggestions.insert(word);
        }
        // insert back
        word.insert(i, 1, temp);
    }
}

void SpellChecker::suggest_adjacent(const string &a_word, set<string> &suggestions) const {
    string word(a_word);
    int len = word.length();
    char temp;
    for (int i = 1; i < len; i++) {
        // swap i-1 -th and i-th letters
        temp = word[i - 1];
        word[i - 1] = word[i];
        word[i] = temp;
        if (d_search(word)) {
            suggestions.insert(word);
        }
        word[i] = word[i - 1];
        word[i - 1] = temp;
    }
}















