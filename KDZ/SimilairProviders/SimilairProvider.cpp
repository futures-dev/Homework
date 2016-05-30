//
// Andrei Kolomiets 143-1
// CLion 2016.1.2 MinGW 3.21 GCC 4.9.1
// 22.05.2016
//

#include <cstring>
#include <iostream>
#include "SimilairProvider.h"

using namespace std;

void SimilairProvider::suggest_replacement(const string &a_word, const StringContainer &dict,
                                           vector<string> &suggestions) const {
    int len = a_word.length();
    char *word = new char[len + 1];
    strcpy(word, a_word.c_str());
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
            string tmp(word);
            if (dict.search(tmp)) {
                suggestions.push_back(tmp);
            }
        }
        word[i] = temp;
    }
}