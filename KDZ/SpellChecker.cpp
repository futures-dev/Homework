//
// Andrei Kolomiets 143-1
// CLion 1.2 MinGW 3.4.1
// 22.05.2016
//

#include "SpellChecker.h"
#include <algorithm>
#include <fstream>
#include <stdexcept>
#include <regex>
#include <iostream>

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
    regex e(wordRegex, regex_constants::extended);
    while (getline(fin, buf)) {
        smatch match;
        regex_search(buf, match, e);
        for (auto word:match) {
            string tmp(word.str());
            transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);
            if (!tmp.empty()) {
                dwd_insert(tmp);
            }
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
    set<string> ignored;
    set<pair<string, string>> replacements;
    while (getline(fin, buf)) {
        smatch match;
        string prev_suffix;
        while (regex_search(buf, match, e)) {
            prev_suffix = match.suffix();
            fout << match.prefix();
            string word(match.str());
            transform(word.begin(), word.end(), word.begin(), ::tolower);
            buf = match.suffix();

            // check ignore all
            if (ignored.find(word) != ignored.end()) {
                fout << word;
                continue;
            }

            // check replace all
            {
                auto rep = find_if(replacements.begin(), replacements.end(), [word](const pair<string, string> &q) {
                    return q.first == word;
                });
                if (rep != replacements.end()) {
                    fout << rep->second;
                    continue;
                }
            }

            // check dictionary
            if (!d_search(word)) {
                cout << "Обнаружено слово " << word << " - оно отсутствует в словаре" << endl;
                bool bad_action1 = true;
                while (bad_action1) {
                    cout << POSSIBLE_ACTIONS_STRING << endl;
                    string action_buf;
                    //getline(cin, action_buf);
                    //switch (action_buf.back()) {
                    switch ('I') {
                        case 'R':
                        case 'r': {
                            cout << "Возможно, имелось в виду:" << endl;
                            set<string> suggestions;
                            suggest_adjacent(word, suggestions);
                            suggest_insertion(word, suggestions);
                            suggest_odd(word, suggestions);
                            suggest_replacement(word, suggestions);
                            string suggested;
                            int i = 0;
                            for (auto it = suggestions.begin(); it != suggestions.end(); it++, i++) {
                                cout << i << ". " << *it << endl;
                            }
                            while (true) {
                                cout << POSSIBLE_REPLACEMENTS_STRING << endl;
                                string action_buf2;
                                getline(cin, action_buf2);
                                if (action_buf2 == "I") {
                                    goto case_ignore;
                                }
                                stringstream myStream(action_buf2);
                                int number;
                                if (myStream >> number) {
                                    if (number < i) {
                                        i = 0;
                                        auto it = suggestions.begin();
                                        while (i++ < number) {
                                            it++;
                                        }
                                        suggested = *it;
                                        fout << suggested;
                                        break;
                                    }
                                }
                            }

                            cout << REPLACE_ALL_STRING << endl;
                            bool bad_action4 = true;
                            string action_buf4;
                            while (bad_action4) {
                                getline(cin, action_buf4);
                                switch (action_buf4.back()) {
                                    case 'A':
                                    case 'a':
                                        replacements.emplace(word, suggested);
                                        bad_action4 = false;
                                        break;
                                    case 'S':
                                    case 's':
                                        bad_action4 = false;
                                        break;
                                    default:
                                        break;
                                }
                            }

                            bad_action1 = false;
                            break;
                        }
                        case_ignore:
                        case 'I':
                        case 'i': {
                            fout << word;
                            cout << IGNORE_ALL_STRING << endl;
                            bool bad_action3 = true;
                            string action_buf3;
                            while (bad_action3) {
                                //getline(cin, action_buf3);
                                //switch (action_buf3.back()) {
                                switch ('A') {
                                    case 'A':
                                    case 'a':
                                        ignored.insert(word);
                                        bad_action3 = false;
                                        break;
                                    case 'S':
                                    case 's':
                                        bad_action3 = false;
                                        break;
                                    default:
                                        break;
                                }
                            }
                            bad_action1 = false;
                            break;
                        }
                        case 'X':
                        case 'x':
                            return;
                        default:
                            break;
                    }
                }
            }
            else {
                fout << word;
            }
        }
        fout << prev_suffix << endl;
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


unsigned char SpellChecker::hash(const std::string &str) const {
    // Rot13
    unsigned int hash = 0;
    int len = str.length();
    for (int i = 0; i < len; i++) {
        hash += (unsigned char) (str[i]);
        hash -= (hash << 13) | (hash >> 19);
    }
    return (unsigned char) hash;
}